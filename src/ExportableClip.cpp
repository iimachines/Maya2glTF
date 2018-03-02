#include "externals.h"
#include "ExportableClip.h"
#include "ExportableNode.h"
#include "Transform.h"

template <typename T>
ExportableProp<T>::ExportableProp(const int frameCount)
{
	values.resize(frameCount);
}

ExportableClip::ExportableClip(
	const ExportableNode& node,
	const std::string& name,
	const int frameCount)
	: name(name)
	, node(node)
	, m_allOrthogonalAxes(true)
{
	m_objectTransforms.resize(frameCount);
}

void ExportableClip::sampleAt(const int frameIndex)
{
	const auto objectMatrix = Transform::getObjectSpaceMatrix(node.dagPath);
	m_allOrthogonalAxes &= Transform::hasOrthogonalAxes(objectMatrix);
	m_objectTransforms.at(frameIndex) = objectMatrix;
}
