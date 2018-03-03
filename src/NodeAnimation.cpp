#include "externals.h"
#include "NodeAnimation.h"
#include "ExportableNode.h"
#include "Transform.h"
#include "OutputStreamsPatch.h"

NodeAnimation::NodeAnimation(
	const ExportableNode& node,
	const int frameCount,
	const double scaleFactor)
	: node(node)
	, m_scaleFactor(scaleFactor)
	, m_allOrthogonalAxes(true)
{
	m_objectMatrices.resize(frameCount);
}

void NodeAnimation::sampleAt(const int frameIndex)
{
	const auto objectMatrix = Transform::getObjectSpaceMatrix(node.dagPath, node.parentDagPath);
	m_allOrthogonalAxes &= Transform::hasOrthogonalAxes(objectMatrix);
	m_objectMatrices.at(frameIndex) = objectMatrix;
}

void NodeAnimation::exportTo(GLTF::Accessor& timesPerFrame, GLTF::Animation& glAnimation)
{
	if (!m_allOrthogonalAxes)
	{
		// TODO: Use SVG to decompose the 3x3 matrix into a product of rotation and scale matrices.
		cerr << prefix << "WARNING: Skewed/sheared matrices are not representable by glTF! Node: " << node.dagPath.fullPathName().asChar() << endl;
	}

	m_positions = std::make_unique<AnimatedT>(timesPerFrame, node.glNode, GLTF::Animation::Path::TRANSLATION);
	m_rotations = std::make_unique<AnimatedR>(timesPerFrame, node.glNode, GLTF::Animation::Path::ROTATION);
	m_scales = std::make_unique<AnimatedS>(timesPerFrame, node.glNode, GLTF::Animation::Path::SCALE);

	for (auto& matrix: m_objectMatrices)
	{
		const auto keyTRS = Transform::toTRS(matrix, m_scaleFactor);

		//double x = keyTRS.rotation[0];
		//double y = keyTRS.rotation[1];
		//double z = keyTRS.rotation[2];
		//double w = keyTRS.rotation[3];

		//double l = x * x + y * y + z * z + w * w;

		//if (abs(l-1) > 1e-6)
		//{
		//	auto glm = Transform::toGLTF(matrix);

		//	cerr << l << " should be one for matrix ";

		//	for (int i=0; i<16; ++i)
		//	{
		//		cerr << glm.matrix[i];
		//		cerr << ' ';
		//	}

		//	cerr << endl;
		//}

		m_positions->valuesPerFrame.emplace_back(reinterpret_array(keyTRS.translation));
		m_rotations->valuesPerFrame.emplace_back(reinterpret_array(keyTRS.rotation));
		m_scales->valuesPerFrame.emplace_back(reinterpret_array(keyTRS.scale));
	}

	// Now create the glTF animations, but only for those props that animate
	const auto nodeTRS = node.transform;
	finish(glAnimation, m_positions, nodeTRS.translation);
	finish(glAnimation, m_rotations, nodeTRS.rotation);
	finish(glAnimation, m_scales, nodeTRS.scale);
}
