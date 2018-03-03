#pragma once

namespace Transform
{
	bool hasOrthogonalAxes(const MMatrix& m, const double epsilon = 1e-3f);

	GLTF::Node::TransformMatrix&& toGLTF(const MMatrix& matrix);

	MMatrix&& getObjectSpaceMatrix(MDagPath childPath);

	GLTF::Node::TransformTRS&& toTRS(const MMatrix& localMatrix, const double scaleFactor, const double precision = 1e9);
	GLTF::Node::TransformTRS&& toTRS(const MMatrix& matrix, const double scaleFactor, const char* context, const double precision = 1e9);
}