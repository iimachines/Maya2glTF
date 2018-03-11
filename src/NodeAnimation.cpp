#include "externals.h"
#include "NodeAnimation.h"
#include "ExportableNode.h"
#include "ExportableMesh.h"
#include "Transform.h"
#include "OutputStreamsPatch.h"

NodeAnimation::NodeAnimation(
	const ExportableNode& node,
	const int frameCount,
	const double scaleFactor)
	: node(node)
	, mesh(node.mesh())
	, m_scaleFactor(scaleFactor)
	, m_allOrthogonalAxes(true)
{
	m_objectMatrices.resize(frameCount);

	if (mesh)
	{
		m_targetWeights.resize(frameCount * mesh->blendShapeCount());
	}
}

void NodeAnimation::sampleAt(const int frameIndex)
{
	const auto objectMatrix = Transform::getObjectSpaceMatrix(node.dagPath, node.parentDagPath);
	m_allOrthogonalAxes &= Transform::hasOrthogonalAxes(objectMatrix);
	m_objectMatrices.at(frameIndex) = objectMatrix;

	if (mesh)
	{
		const auto weightCount = mesh->blendShapeCount();
		if (weightCount)
		{
			auto weights = mesh->getCurrentWeights();
			assert(weights.size() == weightCount);
			std::copy_n(weights.begin(), weightCount, m_targetWeights.begin() + frameIndex * weightCount);
		}
	}
}

void NodeAnimation::exportTo(GLTF::Accessor& timesPerFrame, GLTF::Animation& glAnimation)
{
	if (!m_allOrthogonalAxes)
	{
		// TODO: Use SVG to decompose the 3x3 matrix into a product of rotation and scale matrices.
		cerr << prefix << "WARNING: Skewed/sheared matrices are not representable by glTF! Node: " << node.dagPath.fullPathName().asChar() << endl;
	}

	m_positions = std::make_unique<AnimatedT>(timesPerFrame, node.glNode, GLTF::Animation::Path::TRANSLATION, 3);
	m_rotations = std::make_unique<AnimatedR>(timesPerFrame, node.glNode, GLTF::Animation::Path::ROTATION, 4);
	m_scales = std::make_unique<AnimatedS>(timesPerFrame, node.glNode, GLTF::Animation::Path::SCALE, 3);

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

		m_positions->append(gsl::make_span(keyTRS.translation));
		m_rotations->append(gsl::make_span(keyTRS.rotation));
		m_scales->append(gsl::make_span(keyTRS.scale));
	}

	m_objectMatrices.clear();

	// Now create the glTF animations, but only for those props that animate
	const auto nodeTRS = node.initialTransform;
	finish(glAnimation, m_positions, nodeTRS.translation);
	finish(glAnimation, m_rotations, nodeTRS.rotation);
	finish(glAnimation, m_scales, nodeTRS.scale);

	// Morph target weights
	if (!m_targetWeights.empty())
	{
		auto initialWeights = mesh->getInitialWeights();
		m_weights = std::make_unique<AnimatedW>(timesPerFrame, node.glNode, GLTF::Animation::Path::WEIGHTS, initialWeights.size());
		m_weights->componentValuesPerFrame = move(m_targetWeights);
		finish(glAnimation, m_weights, initialWeights);
	}
}

void NodeAnimation::finish(
	GLTF::Animation& glAnimation, 
	std::unique_ptr<PropAnimation>& animatedProp,
    const gsl::span<const float>& baseValues) const
{
	const auto dimension = animatedProp->dimension;
	assert(dimension == baseValues.size());

	auto& componentValues = animatedProp->componentValuesPerFrame;

	bool isFrozen = true;

	for (size_t offset = 0; offset < componentValues.size() && isFrozen; offset += dimension)
	{
		for (size_t index = 0; index < dimension && isFrozen; ++index)
		{
			isFrozen = std::abs(baseValues[index] - componentValues[offset + index]) < 1e-9;
		}
	}

	if (isFrozen)
	{
		animatedProp.release();
	}
	else
	{
		animatedProp->finish();
		glAnimation.channels.push_back(&animatedProp->glChannel);
	}
}
