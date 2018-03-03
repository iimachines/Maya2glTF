#pragma once

namespace Transform
{
	bool hasOrthogonalAxes(const MMatrix& m, const double epsilon = 1e-3f);

	GLTF::Node::TransformMatrix&& toGLTF(const MMatrix& matrix);

	MMatrix&& getObjectSpaceMatrix(MDagPath childPath);

	GLTF::Node::TransformTRS&& toTRS(const MMatrix& matrix, const char* context);
}