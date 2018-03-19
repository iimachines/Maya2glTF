#pragma once

#include "spans.h"
#include "sceneTypes.h"
#include "MeshRenderables.h"

inline GLTF::Accessor::Type glAccessorType(const size_t dimension)
{
	switch (dimension)
	{
	case 1:
		return GLTF::Accessor::Type::SCALAR;
	case 2:
		return GLTF::Accessor::Type::VEC2;
	case 3:
		return GLTF::Accessor::Type::VEC3;
	case 4:
		return GLTF::Accessor::Type::VEC4;
	case 8:
		return GLTF::Accessor::Type::MAT2;
	case 12:
		return GLTF::Accessor::Type::MAT3;
	case 16:
		return GLTF::Accessor::Type::MAT4;
	default:
		assert(false);
		return GLTF::Accessor::Type::UNKNOWN;
	}
}

template<typename T>
std::unique_ptr<GLTF::Accessor> contiguousAccessor(
	const std::string name,
	GLTF::Accessor::Type type,
	GLTF::Constants::WebGL componentType,
	GLTF::Constants::WebGL target,
	const gsl::span<const T> data,
	const size_t dimension)
{
	auto bytes = reinterpret_span<byte>(data);
	auto accessor = std::make_unique<GLTF::Accessor>(
		type,
		componentType,
		const_cast<byte*>(&bytes[0]),
		int(data.size() / dimension),
		target);

	if (!name.empty())
	{
		accessor->name = name;
	}

	return accessor;
}

inline std::unique_ptr<GLTF::Accessor> contiguousChannelAccessor(
	const std::string name,
	const gsl::span<const float>& data,
	const size_t dimension,
	const GLTF::Constants::WebGL target = static_cast<GLTF::Constants::WebGL>(-1))
{
	return contiguousAccessor(name,
		glAccessorType(dimension),
		GLTF::Constants::WebGL::FLOAT,
		target,
		data,
		dimension);
}

inline std::unique_ptr<GLTF::Accessor> contiguousElementAccessor(
	const Semantic::Kind semantic,
	const ShapeIndex& shapeIndex,
	const gsl::span<const byte>& bytes)
{
	const auto dim = dimension(semantic, shapeIndex);

	switch (Component::type(semantic))
	{
	case Component::FLOAT: 
		return contiguousAccessor(name(semantic),
			glAccessorType(dim),
			GLTF::Constants::WebGL::FLOAT,
			GLTF::Constants::WebGL::ARRAY_BUFFER,
			reinterpret_span<float>(bytes),
			dim);

	case Component::USHORT: 
		return contiguousAccessor(name(semantic),
			glAccessorType(dim),
			GLTF::Constants::WebGL::UNSIGNED_SHORT,
			GLTF::Constants::WebGL::ARRAY_BUFFER,
			reinterpret_span<ushort>(bytes),
			dim);

	default:
		assert(false);
		return nullptr;
	}
}
