#include "externals.h"
#include "ExportableAsset.h"
#include "Arguments.h"

ExportableAsset::ExportableAsset(GLTF::Asset& glAsset, const Arguments& args)
{
	const auto buffer = glAsset.packAccessors();

	// Generate glTF JSON file
	rapidjson::StringBuffer jsonStringBuffer;
	rapidjson::Writer<rapidjson::StringBuffer> jsonWriter(jsonStringBuffer);
	jsonWriter.StartObject();

	const auto embed = !args.glb && !args.separate;

	GLTF::Options options;
	options.embeddedBuffers = embed;
	options.embeddedShaders = embed;
	options.embeddedTextures = embed;
	options.name = args.sceneName.asChar();
	options.binary = args.glb;

	glAsset.writeJSON(&jsonWriter, &options);
	jsonWriter.EndObject();

	m_rawJsonString = jsonStringBuffer.GetString();

	const auto outputFolder = path(args.outputFolder.asChar());
	create_directories(outputFolder);

	const auto outputFilename = std::string(args.sceneName.asChar()) + (args.glb ? ".glb" : ".glTF");
	const auto outputPath = outputFolder / outputFilename;

	cout << "Writing glTF file to '" << outputPath << "'" << endl;

	if (!options.embeddedTextures) {
		for (GLTF::Image* image : glAsset.getAllImages()) {
			path uri = outputFolder / image->uri;
			std::ofstream file;
			create(file, uri.generic_string(), ios::out | ios::binary);
			file.write(reinterpret_cast<char*>(image->data), image->byteLength);
			file.close();
		}
	}

	if (!options.embeddedBuffers) {
		path uri = outputFolder / buffer->uri;
		std::ofstream file;
		create(file, uri.generic_string(), ios::out | ios::binary);
		file.write(reinterpret_cast<char*>(buffer->data), buffer->byteLength);
		file.close();
	}

	if (!options.embeddedShaders) {
		for (GLTF::Shader* shader : glAsset.getAllShaders()) {
			path uri = outputFolder / shader->uri;
			std::ofstream file;
			create(file, uri.generic_string(), ios::out | ios::binary);
			file.write(shader->source.c_str(), shader->source.length());
			file.close();
		}
	}

	// Write glTF file.
	{
		const auto& jsonString = m_rawJsonString;

		std::ofstream file;
		create(file, outputPath.string(), ios::out | (args.glb ? ios::binary : 0));

		if (args.glb)
		{
			file.write("glTF", 4); // magic header

			const auto writeHeader = new uint32_t[2];
			writeHeader[0] = 2; // version

			const int jsonLength = static_cast<int>(jsonString.length());
			const int jsonPadding = (4 - (jsonLength & 3)) & 3;
			const int binPadding = (4 - (buffer->byteLength & 3)) & 3;

			const int headerLength = 12;
			const int chunkHeaderLength = 8;

			writeHeader[1] = headerLength +
				(chunkHeaderLength + jsonLength + jsonPadding) +
				(chunkHeaderLength + buffer->byteLength + binPadding); // length

			file.write(reinterpret_cast<char*>(writeHeader), sizeof(uint32_t) * 2); // GLB header

			writeHeader[0] = jsonLength + jsonPadding; // chunkLength
			writeHeader[1] = 0x4E4F534A; // chunkType JSON
			file.write(reinterpret_cast<char*>(writeHeader), sizeof(uint32_t) * 2);

			file.write(jsonString.c_str(), jsonLength);
			for (int i = 0; i < jsonPadding; i++) {
				file.write(" ", 1);
			}

			writeHeader[0] = buffer->byteLength + binPadding; // chunkLength
			writeHeader[1] = 0x004E4942; // chunkType BIN
			file.write(reinterpret_cast<char*>(writeHeader), sizeof(uint32_t) * 2);

			file.write(reinterpret_cast<char*>(buffer->data), buffer->byteLength);
			for (int i = 0; i < binPadding; i++) {
				file.write("\0", 1);
			}
		}
		else
		{
			file << prettyJsonString() << endl;
		}

		file.close();
	}
}


ExportableAsset::~ExportableAsset()
{
}

void ExportableAsset::create(std::ofstream& file, const std::string& path, const std::ios_base::openmode mode)
{
	file.open(path, mode);

	if (!file.is_open())
	{
		std::ostringstream ss;
		ss << "Couldn't write to '" << path << "'";
		throw std::exception(ss.str().c_str());
	}
}

const std::string& ExportableAsset::prettyJsonString() const
{
	if (m_prettyJsonString.empty() && !m_rawJsonString.empty())
	{
		// Pretty format the JSON
		rapidjson::Document jsonDocument;
		jsonDocument.Parse(m_rawJsonString.c_str());

		rapidjson::StringBuffer jsonPrettyBuffer;
		rapidjson::PrettyWriter<rapidjson::StringBuffer> jsonPrettyWriter(jsonPrettyBuffer);
		jsonDocument.Accept(jsonPrettyWriter);

		m_prettyJsonString = jsonPrettyBuffer.GetString();
	}

	return m_prettyJsonString;
}

