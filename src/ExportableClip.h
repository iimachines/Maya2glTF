#pragma once

#include "NodeAnimation.h"
#include "ExportableFrames.h"
#include "Arguments.h"

class ExportableClip
{
public:
	ExportableClip(const Arguments& args, const AnimClipArg& clipArg, const ExportableScene& scene);
	virtual ~ExportableClip();

	GLTF::Animation glAnimation;

    void getAllAccessors(std::vector<GLTF::Accessor*>& accessors) const;

private:
	ExportableFrames m_frames;
	std::vector<std::unique_ptr<NodeAnimation>> m_nodeAnimations;

	DISALLOW_COPY_MOVE_ASSIGN(ExportableClip);
};
