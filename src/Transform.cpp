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

	GLTF::Node::TransformTRS&& toTRS(const MMatrix& matrix, const char* context)
	{
		if (!hasOrthogonalAxes(matrix))
		{
			cerr << prefix << "WARNING: Skewed/sheared matrices are not representable by glTF! " << context << endl;
		}

		GLTF::Node::TransformTRS trs;
		toGLTF(matrix).getTransformTRS(&trs);
		return std::move(trs);
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
