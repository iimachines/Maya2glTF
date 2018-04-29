#pragma once

#include "macros.h"

class ExportableFrames
{
public:
	ExportableFrames(std::string accessorName, int frameCount, double framesPerSecond);
	~ExportableFrames() = default;

	const int count;

	// For each animation frame, the clip-relative time in seconds.
	std::vector<float> times;

	std::unique_ptr<GLTF::Accessor> glInputs;

private:
	DISALLOW_COPY_MOVE_ASSIGN(ExportableFrames);
};
