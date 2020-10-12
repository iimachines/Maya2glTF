#include "externals.h"

#include "ExportableNode.h"
#include "ExportableScene.h"
#include "MayaException.h"

ExportableScene::ExportableScene(ExportableResources &resources) : m_resources(resources) {}

ExportableScene::~ExportableScene() = default;

void ExportableScene::updateCurrentValues() {
    for (auto &&pair : m_table) {
        auto &node = pair.second;
        node->updateNodeTransforms(m_currentTransformCache);
        auto *mesh = node->mesh();
        if (mesh) {
            mesh->updateWeights();
        }
    }
}

void ExportableScene::mergeRedundantShapeNodes() {
    std::set<NodeTable::key_type> redundantKeys;

    for (auto &&pair : m_table) {
        auto &node = pair.second;
        if (node->tryMergeRedundantShapeNode()) {
            redundantKeys.insert(pair.first);
        }
    }

    for (auto &&key : redundantKeys) {
        m_table.erase(key);
    }
}

ExportableNode *ExportableScene::getNode(const MDagPath &dagPath) {
    MStatus status;

    const std::string fullDagPath{dagPath.fullPathName(&status).asChar()};
    THROW_ON_FAILURE(status);

    MObject mayaNode = dagPath.node(&status);
    if (mayaNode.isNull() || status.error()) {
        cerr << "glTF2Maya: skipping '" << fullDagPath << "' as it is not a node" << endl;
        return nullptr;
    }

    auto &ptr = m_table[fullDagPath];
    if (ptr == nullptr) {
        ptr.reset(new ExportableNode(dagPath));
        ptr->load(*this, m_initialTransformCache);
    }
    return ptr.get();
}

ExportableNode *ExportableScene::getParent(ExportableNode *node) {
    auto dagPath = node->dagPath;

    ExportableNode *parentNode = nullptr;

    MDagPath parentDagPath;
    if (findLogicalParent(dagPath, parentDagPath)) {
        // Logical parent overrides Maya's parent.
        // TODO: Check for cycles!
        parentNode = getNode(parentDagPath);
    }

    // Find first ancestor that is a Maya node.
    // That will become our glTF parent.
    while (!parentNode) {
        dagPath.pop();
        if (dagPath.length() <= 0)
            break;

        parentNode = getNode(dagPath);
    }

    return parentNode;
}

void ExportableScene::getAllAccessors(AccessorsPerDagPath &accessors) {
    for (auto &&pair : m_table) {
        auto &node = pair.second;

        node->getAllAccessors(accessors[node->dagPath]);
    }
}

void ExportableScene::registerOrphanNode(ExportableNode *node) { m_orphans[node->dagPath] = node; }

// int ExportableScene::distanceToRoot(MDagPath dagPath) {
//     int distance;
//
//     // Find first ancestor node.
//     // That is our logical parent.
//     for (distance = 0; dagPath.length() > 0; ++distance) {
//         dagPath.pop();
//     }
//
//     return distance;
// }

bool ExportableScene::findLogicalParent(const MFnDagNode &childDagNode, MDagPath &parentDagPath) {
    parentDagPath = MDagPath();

    const auto childName = childDagNode.partialPathName();

    const auto logicalParentPlug = childDagNode.findPlug("Maya2glTF_LogicalParent");
    if (logicalParentPlug.isNull())
        return false;

    MString logicalParentName;
    if (!logicalParentPlug.getValue(logicalParentName))
        return false;

    MSelectionList selection;
    selection.add(logicalParentName);
    if (selection.length() == 0) {
        cout << prefix << "WARNING: Logical parent '" << logicalParentName.asChar() << " not found on node '"
             << childName << "'" << endl;
        return false;
    }

    if (selection.length() > 1) {
        cout << prefix << "WARNING: More than one logical parent matching '" << logicalParentName.asChar()
             << " was found on node '" << childName << "'" << endl;
        return false;
    }

    MDagPath logicalParentDagPath;
    if (!selection.getDagPath(0, logicalParentDagPath)) {
        cout << prefix << "WARNING: Failed to get DAG path of logical parent '" << logicalParentName.asChar()
             << " on node '" << childName << "'" << endl;
        return false;
    }

    parentDagPath = logicalParentDagPath;
    cout << prefix << "Found logical parent '" << logicalParentDagPath.partialPathName().asChar() << " on node '"
         << childName << "'" << endl;
    return true;
}
