#pragma once
#include "ExportableResources.h"
#include "ExportableClip.h"
#include "ExportableScene.h"

class Arguments;

// A packed buffer and a filename hint.
typedef std::map<GLTF::Buffer*, std::string> PackedBufferMap;

class ExportableAsset
{
public:
	ExportableAsset(const Arguments& args);
	~ExportableAsset();

	const std::string& prettyJsonString() const;

	void save();

private:
	DISALLOW_COPY_MOVE_ASSIGN(ExportableAsset);

	struct Cleanup
	{
		MTime currentTime;

		Cleanup();
		~Cleanup();
	};

	Cleanup m_cleanup;

	GLTF::Asset m_glAsset;
	GLTF::Asset::Metadata m_glMetadata;
	GLTF::Node m_glRootNode;
	GLTF::Node::TransformTRS m_glRootTransform;

	ExportableResources m_resources;
	ExportableScene m_scene;

	//std::vector<std::unique_ptr<ExportableItem>> m_items;
	std::vector<std::unique_ptr<ExportableClip>> m_clips;

    std::map<std::string, GLTF::Buffer> m_bufferByRefName;

	std::string m_rawJsonString;
	mutable std::string m_prettyJsonString;

    void dumpAccessorComponents(const std::vector<GLTF::Accessor*>& accessors) const;

    void packMeshAccessors(AccessorsPerDagPath& accessors, class AccessorPacker& packer, PackedBufferMap& packedBufferMap, std::string namePrefix) const;

	static void create(std::ofstream& file, const std::string& path, const std::ios_base::openmode mode);
};

