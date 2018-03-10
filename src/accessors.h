#pragma once

#include "spans.h"
#include "sceneTypes.h"


template<typename T>
std::unique_ptr<GLTF::Accessor> contiguousAccessor(
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

	if (name)
	{
		accessor->name = name;
	}

	return accessor;
}

template<typename T>
std::unique_ptr<GLTF::Accessor> contiguousChannelAccessor(
	const char* name,
	const gsl::span<T>& data,
	GLTF::Constants::WebGL target = static_cast<GLTF::Constants::WebGL>(-1))
{
	const auto dimension = sizeof(T) / sizeof(float);
	assert(sizeof(T) % sizeof(float) == 0);
	assert(dimension >= 1 && dimension <= 4);

	// HACK: We assume SCALAR == 0 here...
	const auto type = static_cast<GLTF::Accessor::Type>(dimension-1);

	return contiguousAccessor(name,
		type,
		GLTF::Constants::WebGL::FLOAT,
		target,
		data,
		1);
}

template<typename T>
std::unique_ptr<GLTF::Accessor> contiguousElementAccessor(
	const Semantic::Kind semantic,
	const int shapeIndex,
	const gsl::span<T>& data)
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

	return contiguousAccessor(name(semantic),
		type,
		GLTF::Constants::WebGL::FLOAT,
		GLTF::Constants::WebGL::ARRAY_BUFFER,
		reinterpret_span<float>(data),
		dimension(semantic, shapeIndex));
}
