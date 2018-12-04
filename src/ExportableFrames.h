#pragma once

#include "macros.h"

class ExportableFrames
{
public:
	ExportableFrames(const std::string& accessorName, int frameCount, double framesPerSecond);
	~ExportableFrames() = default;

	const int count;

	// For each animation frame, the clip-relative time in seconds.
	std::vector<float> times;

	std::unique_ptr<GLTF::Accessor> glInputs;

    void getAllAccessors(std::vector<GLTF::Accessor*>& accessors) const;

private:
	DISALLOW_COPY_MOVE_ASSIGN(ExportableFrames);
};
