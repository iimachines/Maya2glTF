#include "Transform.h"
#include "ExportableNode.h"
#include "MayaException.h"
#include "externals.h"

const double epsilon = 1e-4f;

// How much the axes deviate from being orthogonal
double getAxesNonOrthogonality(const MMatrix &m) {
    // Maya uses row matrices.
    MVector vx(m[0][0], m[0][1], m[0][2]);
    MVector vy(m[1][0], m[1][1], m[1][2]);
    MVector vz(m[2][0], m[2][1], m[2][2]);

    vx.normalize();
    vy.normalize();
    vz.normalize();

    double e = 0;
    e = std::max(e, fabs(vx * vy));
    e = std::max(e, fabs(vy * vz));
    e = std::max(e, fabs(vz * vx));

    return e;
}

void getTranslation(const MTransformationMatrix &m, float *result,
                    double scaleFactor) {
    const MVector t = m.translation(MSpace::kPostTransform);
    result[0] = roundToFloat(t.x * scaleFactor, posPrecision);
    result[1] = roundToFloat(t.y * scaleFactor, posPrecision);
    result[2] = roundToFloat(t.z * scaleFactor, posPrecision);
}

void getScaling(const MTransformationMatrix &m, float *result) {
    double s[3];
    THROW_ON_FAILURE(m.getScale(s, MSpace::kPostTransform));
    result[0] = roundToFloat(s[0], sclPrecision);
    result[1] = roundToFloat(s[1], sclPrecision);
    result[2] = roundToFloat(s[2], sclPrecision);
}

void getRotation(const MTransformationMatrix &m, float *result) {
    double q[4];
    THROW_ON_FAILURE(m.getRotationQuaternion(q[0], q[1], q[2], q[3]));

    q[0] = roundTo(q[0], dirPrecision);
    q[1] = roundTo(q[1], dirPrecision);
    q[2] = roundTo(q[2], dirPrecision);
    q[3] = roundTo(q[3], dirPrecision);

    MQuaternion mq(q);
    mq.normalizeIt();
    THROW_ON_FAILURE(mq.get(q));

    result[0] = static_cast<float>(q[0]);
    result[1] = static_cast<float>(q[1]);
    result[2] = static_cast<float>(q[2]);
    result[3] = static_cast<float>(q[3]);
}

GLTF::Node::TransformMatrix toGLTF(const MMatrix &matrix) {
    float m[4][4];
    // ReSharper disable once CppExpressionWithoutSideEffects
    matrix.get(m);

    return GLTF::Node::TransformMatrix(
        m[0][0], m[1][0], m[2][0], m[3][0], m[0][1], m[1][1], m[2][1], m[3][1],
        m[0][2], m[1][2], m[2][2], m[3][2], m[0][3], m[1][3], m[2][3], m[3][3]);
}

MMatrix getObjectSpaceMatrix(const MDagPath &dagPath,
                             const MDagPath &parentPath) {
    MStatus status;

    MFnDagNode fnDagNode(dagPath, &status);
    THROW_ON_FAILURE(status);

    const auto childWorldMatrix = dagPath.inclusiveMatrix(&status);
    THROW_ON_FAILURE(status);

    const auto parentPathLength = parentPath.length(&status);
    THROW_ON_FAILURE(status);

    if (parentPathLength == 0)
        return childWorldMatrix;

    const auto parentWorldMatrixInverse =
        parentPath.inclusiveMatrixInverse(&status);
    THROW_ON_FAILURE(status);

    return childWorldMatrix * parentWorldMatrixInverse;
}

void makeIdentity(GLTF::Node::TransformTRS &trs) {
    trs.translation[0] = 0;
    trs.translation[1] = 0;
    trs.translation[2] = 0;

    trs.scale[0] = 1;
    trs.scale[1] = 1;
    trs.scale[2] = 1;

    trs.rotation[0] = 0;
    trs.rotation[1] = 0;
    trs.rotation[2] = 0;
    trs.rotation[3] = 1;
}

const NodeTransformState &
NodeTransformCache::getTransform(const ExportableNode *node,
                                 const double scaleFactor) {
    auto &state = m_table[node];

    if (state.isInitialized > 0)
        return state;

    if (state.isInitialized < 0)
        throw std::runtime_error(
            "Ouch! Infinite loop detected in NodeTransformCache");

    state.isInitialized = -1;

    auto &trs0 = state.localTransforms[0];
    makeIdentity(trs0);

    auto &trs1 = state.localTransforms[1];
    makeIdentity(trs1);

    if (node == nullptr) {
        // World
        state.requiresExtraNode = false;
        state.maxNonOrthogonality = 0;
    } else {
        state.requiresExtraNode = node->transformKind != TransformKind::Simple;

        const auto localMatrix =
            getObjectSpaceMatrix(node->dagPath, node->parentDagPath());

        switch (node->transformKind) {
        case TransformKind::Simple: {
            state.maxNonOrthogonality = getAxesNonOrthogonality(localMatrix);

            // TODO: We're not using the GLTF code here yet, we got
            // non-normalized rotations...
            MTransformationMatrix mayaLocalMatrix(localMatrix);

            auto &trs = state.localTransforms[0];

            getTranslation(mayaLocalMatrix, trs.translation, scaleFactor);
            getRotation(mayaLocalMatrix, trs.rotation);
            getScaling(mayaLocalMatrix, trs.scale);
        } break;

        case TransformKind::ComplexJoint: {
            auto &parentTransform = getTransform(node->parentNode, scaleFactor);
            auto &parentPrimaryTRS = parentTransform.primaryTRS();
            double parentScale[3] = {parentPrimaryTRS.scale[0],
                                     parentPrimaryTRS.scale[1],
                                     parentPrimaryTRS.scale[2]};

            // The local matrix = scale * rotation * inverse-parent-scale *
            // translation Extract and clear the translation, undo  the inverse
            // parent scale, and extract rotation and scale.
            auto m = localMatrix;

            // Get translation
            const auto t = m[3];
            trs1.translation[0] =
                roundToFloat(t[0] * scaleFactor, posPrecision);
            trs1.translation[1] =
                roundToFloat(t[1] * scaleFactor, posPrecision);
            trs1.translation[2] =
                roundToFloat(t[2] * scaleFactor, posPrecision);

            trs1.scale[0] =
                roundToFloat(1.0f / parentPrimaryTRS.scale[0], sclPrecision);
            trs1.scale[1] =
                roundToFloat(1.0f / parentPrimaryTRS.scale[1], sclPrecision);
            trs1.scale[2] =
                roundToFloat(1.0f / parentPrimaryTRS.scale[2], sclPrecision);

            // Clear translation
            t[0] = t[1] = t[2] = 0;

            // Undo the inverse parent transform
            double ps[4][4] = {{parentScale[0], 0, 0, 0},
                               {0, parentScale[1], 0, 0},
                               {0, 0, parentScale[2], 0},
                               {0, 0, 0, 1}};

            m = m * ps;

            state.maxNonOrthogonality = getAxesNonOrthogonality(m);

            const MTransformationMatrix mayaLocalMatrix(m);
            getRotation(mayaLocalMatrix, trs0.rotation);
            getScaling(mayaLocalMatrix, trs0.scale);
        } break;

        case TransformKind::ComplexTransform: {
            MTransformationMatrix pivotTransformationMatrix;
            const MVector pivotOffset = node->pivotPoint - MPoint::origin;
            pivotTransformationMatrix.setTranslation(pivotOffset,
                                                     MSpace::kObject);
            const auto pivotMatrix = pivotTransformationMatrix.asMatrix();

            // cout << "local matrix = " << localMatrix << endl;

            // Decompose localMatrix into inverse(pivotMatrix) * innerMatrix *
            // pivotMatrix Since we combine the pivot translation and local
            // translation, this becomes localMatrix = inverse(pivotMatrix) *
            // combinedMatrix
            // => combinedMatrix = pivotMatrix * localMatrix
            const auto combinedMatrix = pivotMatrix * localMatrix;

            state.maxNonOrthogonality = getAxesNonOrthogonality(combinedMatrix);

            // Inverse pivot translation node
            trs0.translation[0] =
                roundToFloat(-pivotOffset.x * scaleFactor, posPrecision);
            trs0.translation[1] =
                roundToFloat(-pivotOffset.y * scaleFactor, posPrecision);
            trs0.translation[2] =
                roundToFloat(-pivotOffset.z * scaleFactor, posPrecision);

            // TODO: We're not using the GLTF code here yet, we got
            // non-normalized rotations...
            const MTransformationMatrix mayaMatrix(combinedMatrix);

            // trs1: scale, rotation and translation + pivot-offset combined
            getTranslation(mayaMatrix, trs1.translation, scaleFactor);
            getRotation(mayaMatrix, trs1.rotation);
            getScaling(mayaMatrix, trs1.scale);
        } break;

        default:
            throw std::runtime_error("Unsupported node transform kind");
        }
    }

    state.isInitialized = 1;

    return state;
}
