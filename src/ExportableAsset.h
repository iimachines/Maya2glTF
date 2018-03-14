#pragma once
#include "ExportableResources.h"
#include "ExportableClip.h"
#include "NodeHierarchy.h"

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
	GLTF::Scene m_glScene;
	GLTF::Asset::Metadata m_glMetadata;

	ExportableResources m_resources;

	std::vector<std::unique_ptr<ExportableItem>> m_items;
	std::vector<std::unique_ptr<ExportableClip>> m_clips;
	NodeHierarchy m_dagNodeTable;

	std::string m_rawJsonString;
	mutable std::string m_prettyJsonString;

	void addNode(MDagPath& dagPath);

	static void create(std::ofstream& file, const std::string& path, const std::ios_base::openmode mode);
};

