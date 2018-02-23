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
	
	ExportablePrimitive(const VertexBuffer& vertexBuffer, ExportableResources& resources, 
		const Semantic::Kind debugSemantic, const double debugLineLength, const Color debugLineColor);
	
	virtual ~ExportablePrimitive();

	GLTF::Primitive glPrimitive;
	std::unique_ptr<GLTF::Accessor> glIndices;
	MeshAccessorPerSetIndexTable glAccessorTable;

private:
	template<typename T>
	std::unique_ptr<GLTF::Accessor> createAccessor(
		const char* name,
		GLTF::Accessor::Type type,
		GLTF::Constants::WebGL componentType,
		GLTF::Constants::WebGL target,
		const gsl::span<T>& data,
		const size_t dimension)
	{
		const uint8* ptr = &reinterpret_span<uint8>(data)[0];
		auto accessor = std::make_unique<GLTF::Accessor>(type, componentType,
			const_cast<uint8*>(ptr),
			static_cast<int>(data.size() / dimension),
			target);

		accessor->name = name;
		return accessor;
	}

	template<typename T>
	std::unique_ptr<GLTF::Accessor> createFloatAccessor(
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

		return createAccessor(name(semantic), 
			type, 
			GLTF::Constants::WebGL::FLOAT, 
			GLTF::Constants::WebGL::ARRAY_BUFFER, 
			reinterpret_span<float>(buffer), 
			dimension(semantic));
	}
};
