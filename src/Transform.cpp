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
	matrix.get(m);

	return std::move(GLTF::Node::TransformMatrix(
		m[0][0], m[1][0], m[2][0], m[3][0],
		m[0][1], m[1][1], m[2][1], m[3][1],
		m[0][2], m[1][2], m[2][2], m[3][2],
		m[0][3], m[1][3], m[2][3], m[3][3]));
}

float cleanupScalar(const double v)
{
	return static_cast<float>(round(v * precision) / precision);
}

GLTF::Node::TransformTRS toTRS(const MMatrix& localMatrix, const double scaleFactor, const char* context, const double precision)
{
	if (!hasOrthogonalAxes(localMatrix))
	{
		// TODO: Use SVG to decompose the 3x3 matrix into a product of rotation and scale matrices.
		cerr << prefix << "WARNING: Skewed/sheared matrices are not representable by glTF! " << context << endl;
	}

	return std::move(toTRS(localMatrix, scaleFactor, precision));
}

MMatrix getObjectSpaceMatrix(const MMatrix& pivotTransform, MDagPath dagPath, MDagPath parentPath)
{
	MStatus status;

	MFnDagNode fnDagNode(dagPath, &status);
	THROW_ON_FAILURE(status);

	const auto childWorldMatrix = dagPath.inclusiveMatrix(&status);
	THROW_ON_FAILURE(status);

	const auto parentPathLength = parentPath.length(&status);
	THROW_ON_FAILURE(status);

	if (parentPathLength == 0)
		return std::move(pivotTransform * childWorldMatrix);

	const auto parentWorldMatrixInverse = parentPath.inclusiveMatrixInverse(&status);
	THROW_ON_FAILURE(status);

	return std::move(pivotTransform * childWorldMatrix * parentWorldMatrixInverse);
}
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

	auto& rs = state.localTransforms[0];
	makeIdentity(rs);

	auto& tu = state.localTransforms[1];
	makeIdentity(tu);

	if (node == nullptr)
	{
		// World 
		state.hasSegmentScaleCompensation = false;
		state.hasValidLocalTransforms = true;
	}
	else
	{
		state.hasSegmentScaleCompensation = node->hasSegmentScaleCompensation;

		const auto localMatrix = getObjectSpaceMatrix(node->dagPath, node->parentDagPath());

		if (state.hasSegmentScaleCompensation)
		{
			auto& parentTransform = getTransform(node->parentNode, scaleFactor);
			auto& parentRS = parentTransform.localTransformRS();
			double parentScale[3] = { parentRS.scale[0], parentRS.scale[1], parentRS.scale[2] };

			// The local matrix = scale * rotation * inverse-parent-scale * translation
			// Extract and clear the translation, undo  the inverse parent scale, and extract rotation and scale.
			auto m = localMatrix;

			// Get translation
			const auto t = m[3];
			tu.translation[0] = cleanupScalar(t[0] * scaleFactor);
			tu.translation[1] = cleanupScalar(t[1] * scaleFactor);
			tu.translation[2] = cleanupScalar(t[2] * scaleFactor);

			tu.scale[0] = 1.0f / parentRS.scale[0];
			tu.scale[1] = 1.0f / parentRS.scale[1];
			tu.scale[2] = 1.0f / parentRS.scale[2];

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

			MTransformationMatrix mayaLocalMatrix(m);

			// Extract rotation 
			double qx, qy, qz, qw;
			mayaLocalMatrix.getRotationQuaternion(qx, qy, qz, qw);
			rs.rotation[0] = cleanupScalar(qx);
			rs.rotation[1] = cleanupScalar(qy);
			rs.rotation[2] = cleanupScalar(qz);
			rs.rotation[3] = cleanupScalar(qw);

			// Extract scale factors
			double scale[3];
			mayaLocalMatrix.getScale(scale, MSpace::kPostTransform);
			rs.scale[0] = cleanupScalar(scale[0]);
			rs.scale[1] = cleanupScalar(scale[1]);
			rs.scale[2] = cleanupScalar(scale[2]);
		}
		else
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
			mayaLocalMatrix.getRotationQuaternion(qx, qy, qz, qw);
			trs.rotation[0] = cleanupScalar(qx);
			trs.rotation[1] = cleanupScalar(qy);
			trs.rotation[2] = cleanupScalar(qz);
			trs.rotation[3] = cleanupScalar(qw);

			// Extract scale factors
			double scale[3];
			mayaLocalMatrix.getScale(scale, MSpace::kPostTransform);
			trs.scale[0] = cleanupScalar(scale[0]);
			trs.scale[1] = cleanupScalar(scale[1]);
			trs.scale[2] = cleanupScalar(scale[2]);
		}
	}

	state.isInitialized = 1;

	return state;
}




