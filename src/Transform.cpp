#include "externals.h"
#include "MayaException.h"
#include "Transform.h"
#include "ExportableNode.h"

const double epsilon = 1e-4f;
const double precision = 1e9;

bool hasOrthogonalAxes(const MMatrix& m)
{
	// Maya uses row matrices.
	const MVector vx(m[0][0], m[0][1], m[0][2]);
	const MVector vy(m[1][0], m[1][1], m[1][2]);
	const MVector vz(m[2][0], m[2][1], m[2][2]);
	return
		fabs(vx*vy) < epsilon &&
		fabs(vy*vz) < epsilon &&
		fabs(vz*vx) < epsilon;
}


GLTF::Node::TransformMatrix toGLTF(const MMatrix& matrix)
{
	float m[4][4];
	// ReSharper disable once CppExpressionWithoutSideEffects
	matrix.get(m);

	return GLTF::Node::TransformMatrix(
		m[0][0], m[1][0], m[2][0], m[3][0],
		m[0][1], m[1][1], m[2][1], m[3][1],
		m[0][2], m[1][2], m[2][2], m[3][2],
		m[0][3], m[1][3], m[2][3], m[3][3]);
}

float cleanupScalar(const double v)
{
	return static_cast<float>(round(v * precision) / precision);
}

MMatrix getObjectSpaceMatrix(const MDagPath& dagPath, const MDagPath& parentPath)
{
	MStatus status;

	MFnDagNode fnDagNode(dagPath, &status);
	THROW_ON_FAILURE(status);

	const auto childWorldMatrix = dagPath.inclusiveMatrix(&status);
	THROW_ON_FAILURE(status);

	const auto parentPathLength = parentPath.length(&status);
	THROW_ON_FAILURE(status);

	if (parentPathLength == 0)
		return childWorldMatrix;

	const auto parentWorldMatrixInverse = parentPath.inclusiveMatrixInverse(&status);
	THROW_ON_FAILURE(status);

	return childWorldMatrix * parentWorldMatrixInverse;
}

void makeIdentity(GLTF::Node::TransformTRS &trs)
{
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


const NodeTransformState& NodeTransformCache::getTransform(const ExportableNode* node, const double scaleFactor)
{
	auto& state = m_table[node];

	if (state.isInitialized > 0)
		return state;

	if (state.isInitialized < 0)
		throw std::runtime_error("Ouch! Infinite loop detected in NodeTransformCache");

	state.isInitialized = -1;

	auto& trs0 = state.localTransforms[0];
	makeIdentity(trs0);

	auto& trs1 = state.localTransforms[1];
	makeIdentity(trs1);

	if (node == nullptr)
	{
		// World 
		state.requiresExtraNode = false;
		state.hasValidLocalTransforms = true;
	}
	else
	{
		state.requiresExtraNode = node->transformKind != TransformKind::Simple;

		const auto localMatrix = getObjectSpaceMatrix(node->dagPath, node->parentDagPath());

		switch (node->transformKind)
		{
		case TransformKind::Simple:
		{
			state.hasValidLocalTransforms = hasOrthogonalAxes(localMatrix);

			// TODO: We're not using the GLTF code here yet, we got non-normalized rotations...
			MTransformationMatrix mayaLocalMatrix(localMatrix);

			auto& trs = state.localTransforms[0];

			// Get translation
			const MVector t = mayaLocalMatrix.translation(MSpace::kPostTransform);
			trs.translation[0] = cleanupScalar(t.x * scaleFactor);
			trs.translation[1] = cleanupScalar(t.y * scaleFactor);
			trs.translation[2] = cleanupScalar(t.z*  scaleFactor);

			// Extract rotation 
			double qx, qy, qz, qw;
			// ReSharper disable once CppExpressionWithoutSideEffects
			mayaLocalMatrix.getRotationQuaternion(qx, qy, qz, qw);
			trs.rotation[0] = cleanupScalar(qx);
			trs.rotation[1] = cleanupScalar(qy);
			trs.rotation[2] = cleanupScalar(qz);
			trs.rotation[3] = cleanupScalar(qw);

			// Extract scale factors
			double scale[3];
			// ReSharper disable once CppExpressionWithoutSideEffects
			mayaLocalMatrix.getScale(scale, MSpace::kPostTransform);
			trs.scale[0] = cleanupScalar(scale[0]);
			trs.scale[1] = cleanupScalar(scale[1]);
			trs.scale[2] = cleanupScalar(scale[2]);
		}
		break;

		case TransformKind::ComplexJoint:
		{
			auto& parentTransform = getTransform(node->parentNode, scaleFactor);
			auto& parentPrimaryTRS = parentTransform.primaryTRS();
			double parentScale[3] = { parentPrimaryTRS.scale[0], parentPrimaryTRS.scale[1], parentPrimaryTRS.scale[2] };

			// The local matrix = scale * rotation * inverse-parent-scale * translation
			// Extract and clear the translation, undo  the inverse parent scale, and extract rotation and scale.
			auto m = localMatrix;

			// Get translation
			const auto t = m[3];
			trs1.translation[0] = cleanupScalar(t[0] * scaleFactor);
			trs1.translation[1] = cleanupScalar(t[1] * scaleFactor);
			trs1.translation[2] = cleanupScalar(t[2] * scaleFactor);

			trs1.scale[0] = 1.0f / parentPrimaryTRS.scale[0];
			trs1.scale[1] = 1.0f / parentPrimaryTRS.scale[1];
			trs1.scale[2] = 1.0f / parentPrimaryTRS.scale[2];

			// Clear translation
			t[0] = t[1] = t[2] = 0;

			// Undo the inverse parent transform
			double ps[4][4] = {
				{ parentScale[0], 0, 0, 0 },
				{ 0, parentScale[1], 0, 0 },
				{ 0, 0, parentScale[2], 0 },
				{ 0, 0, 0, 1 }
			};

			m = m * ps;

			state.hasValidLocalTransforms = hasOrthogonalAxes(m);

			MTransformationMatrix mayaLocalMatrix(m);

			// Extract rotation 
			double qx, qy, qz, qw;
			// ReSharper disable once CppExpressionWithoutSideEffects
			mayaLocalMatrix.getRotationQuaternion(qx, qy, qz, qw);
			trs0.rotation[0] = cleanupScalar(qx);
			trs0.rotation[1] = cleanupScalar(qy);
			trs0.rotation[2] = cleanupScalar(qz);
			trs0.rotation[3] = cleanupScalar(qw);

			// Extract scale factors
			double scale[3];
			// ReSharper disable once CppExpressionWithoutSideEffects
			mayaLocalMatrix.getScale(scale, MSpace::kPostTransform);
			trs0.scale[0] = cleanupScalar(scale[0]);
			trs0.scale[1] = cleanupScalar(scale[1]);
			trs0.scale[2] = cleanupScalar(scale[2]);
		}
		break;

		case TransformKind::ComplexTransform:
		{
			MTransformationMatrix pivotTransformationMatrix;
			const MVector pivotOffset = node->pivotPoint - MPoint::origin;
			pivotTransformationMatrix.setTranslation(pivotOffset, MSpace::kObject);
			const auto pivotMatrix = pivotTransformationMatrix.asMatrix();

			// cout << "local matrix = " << localMatrix << endl;

			// Decompose localMatrix into inverse(pivotMatrix) * innerMatrix * pivotMatrix
			// Since we combine the pivot translation and local translation, this becomes
			// localMatrix = inverse(pivotMatrix) * combinedMatrix
			// => combinedMatrix = pivotMatrix * localMatrix
			const auto combinedMatrix = pivotMatrix * localMatrix;

			state.hasValidLocalTransforms = hasOrthogonalAxes(combinedMatrix);

			// Inverse pivot translation node
			trs0.translation[0] = cleanupScalar(-pivotOffset.x * scaleFactor);
			trs0.translation[1] = cleanupScalar(-pivotOffset.y * scaleFactor);
			trs0.translation[2] = cleanupScalar(-pivotOffset.z*  scaleFactor);

			// TODO: We're not using the GLTF code here yet, we got non-normalized rotations...
			MTransformationMatrix mayaMatrix(combinedMatrix);

			// trs1: scale, rotation and translation + pivot-offset combined

			// Get translation
			const MVector t = mayaMatrix.translation(MSpace::kPostTransform);
			trs1.translation[0] = cleanupScalar(t.x * scaleFactor);
			trs1.translation[1] = cleanupScalar(t.y * scaleFactor);
			trs1.translation[2] = cleanupScalar(t.z*  scaleFactor);

			// Extract rotation 
			double qx, qy, qz, qw;
			// ReSharper disable once CppExpressionWithoutSideEffects
			mayaMatrix.getRotationQuaternion(qx, qy, qz, qw);
			trs1.rotation[0] = cleanupScalar(qx);
			trs1.rotation[1] = cleanupScalar(qy);
			trs1.rotation[2] = cleanupScalar(qz);
			trs1.rotation[3] = cleanupScalar(qw);

			// Extract scale factors
			double scale[3];
			// ReSharper disable once CppExpressionWithoutSideEffects
			mayaMatrix.getScale(scale, MSpace::kPostTransform);
			trs1.scale[0] = cleanupScalar(scale[0]);
			trs1.scale[1] = cleanupScalar(scale[1]);
			trs1.scale[2] = cleanupScalar(scale[2]);
		}
		break;

		default:
			throw std::runtime_error("Unsupported node transform kind");
		}
	}

	state.isInitialized = 1;

	return state;
}




