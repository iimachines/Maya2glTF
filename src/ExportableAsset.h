#pragma once
class Arguments;

class ExportableAsset
{
public:
	ExportableAsset(GLTF::Asset& asset, const Arguments& args);
	~ExportableAsset();

	const std::string& prettyJsonString() const;

private:
	std::string m_rawJsonString;
	mutable std::string m_prettyJsonString;

	static void create(std::ofstream& file, const std::string& path, const std::ios_base::openmode mode);

};

