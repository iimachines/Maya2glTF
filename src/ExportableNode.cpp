#include "externals.h"
#include "ExportableNode.h"
#include "MayaException.h"
#include "ExportableResources.h"
#include "NodeAnimation.h"
#include "Transform.h"
#include "ExportableScene.h"
#include "Arguments.h"
#include "DagHelper.h"

ExportableNode::ExportableNode(const MDagPath& dagPath)
    : ExportableObject(dagPath.node())
    , dagPath(dagPath)
{
}

void ExportableNode::load(
    ExportableScene& scene,
    NodeTransformCache& transformCache)
{
    MStatus status;

    auto& resources = scene.resources();
    auto& args = resources.arguments();

    // Is this a joint with segment scale compensation? (the default in Maya)
    bool maybeSegmentScaleCompensation = false;
    DagHelper::getPlugValue(obj, "segmentScaleCompensate", maybeSegmentScaleCompensation);

    // Remember scale factor
    scaleFactor = args.getBakeScaleFactor();

    // Get name
    const auto name = dagPath.partialPathName(&status);
    THROW_ON_FAILURE(status);

    // Get parent
    parentNode = scene.getParent(this);

    // Deal with segment scale compensation
    // A root joint never has segment scale compensation, since the parent is the world.
    if (maybeSegmentScaleCompensation &&
        parentNode &&
        parentNode->obj.hasFn(MFn::kJoint) &&
        !args.ignoreSegmentScaleCompensation)
    {
        transformKind = TransformKind::ComplexJoint;
    }

    // Deal with pivot points.
    // We currently only support a single pivot point, 
    // but Maya has both a rotation and scaling pivot, 
    // so warn the user if these are different.
    MFnTransform fnTransform(dagPath, &status);
    if (status)
    {
        const auto scalePivot = fnTransform.scalePivot(MSpace::kObject);
        const auto rotatePivot = fnTransform.rotatePivot(MSpace::kObject);

        if (scalePivot != rotatePivot)
        {
            MayaException::printError(formatted("Transform '%s' has different scaling and rotation pivots, this is not supported, ignoring scaling pivot!",
                dagPath.partialPathName().asChar()), MStatus::kNotImplemented);
        }

        pivotPoint = rotatePivot;

        if (pivotPoint != MPoint::origin)
        {
            cout << prefix << "Transform " << dagPath.partialPathName() << " has a pivot point, extra GLTF nodes will be added to handle this" << endl;

            transformKind = TransformKind::ComplexTransform;
        }
    }

    // In the presence of segment scale compensation or pivot points, 
    // parent.TRS <- child.TRS 
    // becomes
    // parent.TU <- parent.RS <- child.TU <- child.RS

    auto& sNode = glSecondaryNode();
    auto& pNode = glPrimaryNode();

    switch (transformKind)
    {
    case TransformKind::ComplexJoint:
        args.assignName(sNode, (name + ":SSC").asChar());
        args.assignName(pNode, name.asChar());
        sNode.children.emplace_back(&pNode);
        break;
    case TransformKind::ComplexTransform:
        args.assignName(pNode, (name + ":PIV").asChar());
        args.assignName(sNode, name.asChar());
        sNode.children.emplace_back(&pNode);
        break;
    default:;
        args.assignName(pNode, name.asChar());
        break;
    }

    if (parentNode)
    {
        // Register as child
        parentNode->glPrimaryNode().children.push_back(&sNode);
    }
    else
    {
        // Register node without parent 
        // We do not yet add the glNode to the glScene,
        // since we might introduce an extra global root node (typically for global scaling)
        scene.registerOrphanNode(this);
    }

    // Get transform
    initialTransformState = transformCache.getTransform(this, scaleFactor);
    m_glNodes[0].transform = &initialTransformState.localTransforms[0];
    m_glNodes[1].transform = &initialTransformState.localTransforms[1];

    if (initialTransformState.maxNonOrthogonality > MAX_NON_ORTHOGONALITY)
    {
        // TODO: Use SVG to decompose the 3x3 matrix into a product of rotation and scale matrices.
        cerr << prefix << "WARNING: node '" << name << "' has initial transforms that are not representable by glTF! Skewing is not supported, use 3 nodes to simulate this. Deviation = " <<
            std::fixed << std::setprecision(2) << initialTransformState.maxNonOrthogonality * 100 << "%" << endl;
    }

    // Create mesh, if any
    // Get mesh, but only if the node was selected.
    if (args.selection.find(dagPath) != args.selection.end())
    {
        MDagPath shapeDagPath = dagPath;
        status = shapeDagPath.extendToShape();

        if (status && shapeDagPath.hasFn(MFn::kMesh))
        {
            // The shape is a mesh
            m_mesh = std::make_unique<ExportableMesh>(scene, *this, shapeDagPath);
            m_mesh->setupNode(pNode);
        }
    }
}

ExportableNode::~ExportableNode() = default;

std::unique_ptr<NodeAnimation> ExportableNode::createAnimation(const ExportableFrames& frameTimes, const double scaleFactor)
{
    return std::make_unique<NodeAnimation>(*this, frameTimes, scaleFactor);
}

void ExportableNode::updateNodeTransforms(NodeTransformCache& transformCache)
{
    currentTransformState = transformCache.getTransform(this, scaleFactor);
    m_glNodes[0].transform = &currentTransformState.localTransforms[0];
    m_glNodes[1].transform = &currentTransformState.localTransforms[1];

    if (currentTransformState.maxNonOrthogonality > MAX_NON_ORTHOGONALITY)
    {
        // TODO: Use SVG to decompose the 3x3 matrix into a product of rotation and scale matrices.
        const auto currentFrameTime = MAnimControl::currentTime();

        cerr << prefix << "WARNING: node '" << name() << "' has transforms at the current frame " << currentFrameTime << " that are not representable by glTF! Skewing is not supported, use 3 nodes to simulate this. Deviation = " 
            << std::fixed << std::setprecision(2) << currentTransformState.maxNonOrthogonality * 100 << "%" << endl;
    }
}

bool ExportableNode::tryMergeRedundantShapeNode()
{
    if (this->mesh() == nullptr)
        return false;

    if (transformKind != TransformKind::Simple)
        return false;

    if (parentNode == nullptr)
        return false;

    if (parentNode->mesh() != nullptr)
        return false;

    auto& glParentNode = parentNode->glPrimaryNode();
    if (glParentNode.children.size() != 1)
        return false;

    auto& glNode = this->glPrimaryNode();

    assert(glParentNode.children.at(0) == &glNode);

    auto& transform = glNode.transform;

    if (transform->type != GLTF::Node::Transform::TRS)
        return false;

    auto* trs = static_cast<const GLTF::Node::TransformTRS*>(transform);
    if (trs->translation[0] != 0 || trs->translation[1] != 0 || trs->translation[2] != 0)
        return false;
    if (trs->rotation[0] != 0 || trs->rotation[1] != 0 || trs->rotation[2] != 0 || trs->rotation[3] != 1)
        return false;
    if (trs->scale[0] != 1 || trs->scale[1] != 1 || trs->scale[2] != 1)
        return false;

    cout << prefix << "Shape node '" << name() << "' is redundant, moving its mesh to parent node '" << parentNode->name() << "'" << endl;

    glParentNode.children.clear();
    glNode.mesh = nullptr;
    glNode.skin = nullptr;

    m_mesh->setupNode(glParentNode);
    m_mesh.swap(parentNode->m_mesh);

    return true;
}
