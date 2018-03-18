#pragma once
#include "ExportableResources.h"
#include "ExportableClip.h"
#include "ExportableScene.h"

class Arguments;

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

	ExportableResources m_resources;
	ExportableScene m_scene;

	//std::vector<std::unique_ptr<ExportableItem>> m_items;
	std::vector<std::unique_ptr<ExportableClip>> m_clips;

	std::string m_rawJsonString;
	mutable std::string m_prettyJsonString;

	static void create(std::ofstream& file, const std::string& path, const std::ios_base::openmode mode);
};

