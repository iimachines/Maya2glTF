#include "externals.h"
#include "ExportableClip.h"
#include "ExportableNode.h"
#include "accessors.h"
#include "time.h"

ExportableClip::ExportableClip(const Arguments& args, const AnimClipArg& clipArg, const ExportableScene& scene)
{
	glAnimation.name = clipArg.name;

	const auto frameCount = clipArg.frameCount();
	const auto scaleFactor = args.scaleFactor;

	auto& items = scene.table();

	m_nodeAnimations.reserve(items.size());

	for (auto& pair : items)
	{
		auto& node = pair.second;
		auto nodeAnimation = node->createAnimation(frameCount, scaleFactor);
		if (nodeAnimation)
		{
			m_nodeAnimations.emplace_back(std::move(nodeAnimation));
		}
	}

	m_timesPerFrame.reserve(frameCount);

	for (auto relativeFrameIndex = 0; relativeFrameIndex < frameCount; ++relativeFrameIndex)
	{
		const double relativeFrameTime = relativeFrameIndex / clipArg.framesPerSecond;
		m_timesPerFrame.push_back(static_cast<float>(relativeFrameTime));

		const MTime absoluteFrameTime = clipArg.startTime + MTime(relativeFrameTime, MTime::kSeconds);
		setCurrentTime(absoluteFrameTime, args.redrawViewport);

		for (auto& nodeAnimation : m_nodeAnimations)
		{
			nodeAnimation->sampleAt(relativeFrameIndex);
		}
	}

	m_inputs = contiguousChannelAccessor("times", span(m_timesPerFrame), 1);

	for (auto& nodeAnimation : m_nodeAnimations)
	{
		nodeAnimation->exportTo(*m_inputs, glAnimation);
	}
}

ExportableClip::~ExportableClip() = default;
