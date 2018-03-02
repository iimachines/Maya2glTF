#pragma once

class ExportableNode;

template<typename T>
class ExportableProp
{
public:
	ExportableProp(const int frameCount);

	std::vector<T> values;

	GLTF::Animation::Channel glChannel;
	GLTF::Animation::Sampler glSampler;
	GLTF::Animation::Channel::Target gl_target;

private:
	DISALLOW_COPY_AND_ASSIGN(ExportableProp);
};

class ExportableClip
{
public:
	ExportableClip(const ExportableNode& node, const std::string& name, const int frameCount);

	virtual ~ExportableClip() = default;

	// Samples values at the current time
	virtual void sampleAt(const int relativeFrameIndex);

	const std::string name;

	const ExportableNode& node;

private:
	bool m_allOrthogonalAxes;
	std::vector<MMatrix> m_objectTransforms;

	DISALLOW_COPY_AND_ASSIGN(ExportableClip);
};
