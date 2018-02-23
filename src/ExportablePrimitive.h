#pragma once

#include "sceneTypes.h"
#include "MeshRenderables.h"
#include "ExportableMesh.h"

typedef std::vector<std::unique_ptr<GLTF::Accessor>> MeshAccessorPerSetIndex;
typedef std::array<MeshAccessorPerSetIndex, Semantic::COUNT> MeshAccessorPerSetIndexTable;

class ExportableResources;

class ExportablePrimitive
{
public:
	ExportablePrimitive(const VertexBuffer& vertexBuffer, ExportableResources& resources);
	ExportablePrimitive(const VertexBuffer& vertexBuffer, ExportableResources& resources, Semantic::Kind debugSemantic, double debugLineLength);
	virtual ~ExportablePrimitive();

	GLTF::Primitive glPrimitive;
	std::unique_ptr<GLTF::Accessor> glIndices;
	MeshAccessorPerSetIndexTable glAccessorTable;

private:
	template<typename T>
	gsl::span<uint8> makeBuffer(const gsl::span<T>& span)
	{
		auto& buffer = m_bufferMap[m_bufferMap.size()];
		auto& source = reinterpret_span<uint8>(span);
		buffer.insert(buffer.end(), source.begin(), source.end());
		return gsl::make_span(buffer);
	}

	template<typename T>
	gsl::span<T> allocBuffer(const size_t capacity)
	{
		auto& buffer = m_bufferMap[m_bufferMap.size()];
		buffer.resize(capacity * sizeof(T));
		return mutable_span(reinterpret_span<T>(buffer));
	}

	std::map<size_t, std::vector<uint8>> m_bufferMap;

	template<typename T>
	std::unique_ptr<GLTF::Accessor> createAccessor(
		GLTF::Accessor::Type type,
		GLTF::Constants::WebGL componentType,
		GLTF::Constants::WebGL target,
		const gsl::span<T>& data)
	{
		const uint8* ptr = &reinterpret_span<uint8>(data)[0];
		return std::make_unique<GLTF::Accessor>(type, componentType,
			const_cast<uint8*>(ptr),
			static_cast<int>(data.size()),
			target);
	}

	template<typename T>
	std::unique_ptr<GLTF::Accessor> createAccessor(
		const Semantic::Kind semantic, 
		const gsl::span<T>& buffer)
	{
		GLTF::Accessor::Type type;

		switch (semantic)
		{
		case Semantic::POSITION:
			type = GLTF::Accessor::Type::VEC3;
			break;
		case Semantic::NORMAL:
			type = GLTF::Accessor::Type::VEC3;
			break;
		case Semantic::TEXCOORD:
			type = GLTF::Accessor::Type::VEC2;
			break;
		case Semantic::TANGENT:
			// TODO: For exporting morph targets, use VEC3
			type = GLTF::Accessor::Type::VEC4;
			break;
		case Semantic::COLOR:
			type = GLTF::Accessor::Type::VEC4;
			break;
		default:
			assert(false);
			return nullptr;
		}

		return createAccessor(type, GLTF::Constants::WebGL::FLOAT, GLTF::Constants::WebGL::ARRAY_BUFFER, buffer);
	}
};
