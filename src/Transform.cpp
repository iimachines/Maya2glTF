#include "externals.h"
#include "MayaException.h"
#include "Transform.h"

namespace Transform
{
	bool hasOrthogonalAxes(const MMatrix& m, const double epsilon)
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


	GLTF::Node::TransformMatrix&& toGLTF(const MMatrix& matrix)
	{
		float m[4][4];
		matrix.get(m);

		return std::move(GLTF::Node::TransformMatrix(
			m[0][0], m[1][0], m[2][0], m[3][0],
			m[0][1], m[1][1], m[2][1], m[3][1],
			m[0][2], m[1][2], m[2][2], m[3][2],
			m[0][3], m[1][3], m[2][3], m[3][3]));
	}

	float cleanupScalar(const double v, const double precision)
	{
		return static_cast<float>(round(v * precision) / precision);
	}

	GLTF::Node::TransformTRS&& toTRS(const MMatrix& localMatrix, const double scaleFactor, const double precision)
	{
		MTransformationMatrix mayaLocalMatrix(localMatrix);

		// TODO: We're not using the GLTF code here yet, we got non-normalized rotations...
		GLTF::Node::TransformTRS trs;

		// Get translation
		MVector t = mayaLocalMatrix.translation(MSpace::kPostTransform);
		trs.translation[0] = cleanupScalar(t.x * scaleFactor, precision);
		trs.translation[1] = cleanupScalar(t.y * scaleFactor, precision);
		trs.translation[2] = cleanupScalar(t.z*  scaleFactor, precision);

		// Calculate rotation data
		double qx, qy, qz, qw;
		mayaLocalMatrix.getRotationQuaternion(qx, qy, qz, qw);
		trs.rotation[0] = cleanupScalar(qx, precision);
		trs.rotation[1] = cleanupScalar(qy, precision);
		trs.rotation[2] = cleanupScalar(qz, precision);
		trs.rotation[3] = cleanupScalar(qw, precision);

		// Get joint scale
		double scale[3];
		mayaLocalMatrix.getScale(scale, MSpace::kPostTransform);
		trs.scale[0] = cleanupScalar(scale[0], precision);
		trs.scale[1] = cleanupScalar(scale[1], precision);
		trs.scale[2] = cleanupScalar(scale[2], precision);

		return std::move(trs);
	}

	GLTF::Node::TransformTRS&& toTRS(const MMatrix& localMatrix, const double scaleFactor, const char* context, const double precision)
	{
		if (!hasOrthogonalAxes(localMatrix))
		{
			// TODO: Use SVG to decompose the 3x3 matrix into a product of rotation and scale matrices.
			cerr << prefix << "WARNING: Skewed/sheared matrices are not representable by glTF! " << context << endl;
		}

		return toTRS(localMatrix, scaleFactor, precision);
	}

	MMatrix&& getObjectSpaceMatrix(MDagPath dagPath)
	{
		MStatus status;

		MFnDagNode fnDagNode(dagPath, &status);
		THROW_ON_FAILURE(status);

		auto childWorldMatrix = dagPath.inclusiveMatrix(&status);
		THROW_ON_FAILURE(status);

		const int pathLength = dagPath.pathCount(&status);
		THROW_ON_FAILURE(status);

		// Root node?
		if (pathLength == 1)
			return std::move(childWorldMatrix);

		// Child node.
		MDagPath parentDagPath;
		status = dagPath.getPath(parentDagPath, std::max(0, pathLength - 1));
		THROW_ON_FAILURE(status);

		const auto parentWorldMatrixInverse = parentDagPath.inclusiveMatrixInverse(&status);
		THROW_ON_FAILURE(status);

		return std::move(childWorldMatrix * parentWorldMatrixInverse);
	}
}
