#include "externals.h"
#include "ExportableFrames.h"
#include "accessors.h"

ExportableFrames::ExportableFrames(
	const std::string& accessorName, 
	const int frameCount, 
	const double framesPerSecond)
	: count(frameCount)
{
	times.reserve(frameCount);

	for (auto relativeFrameIndex = 0; relativeFrameIndex < frameCount; ++relativeFrameIndex)
	{
		const double relativeFrameTime = relativeFrameIndex / framesPerSecond;
		times.emplace_back(static_cast<float>(relativeFrameTime));
	}

	glInputs = contiguousChannelAccessor(accessorName, times, 1);
}

void ExportableFrames::getAllAccessors(std::vector<GLTF::Accessor*>& accessors) const
{
    accessors.emplace_back(glInputs.get());
}
