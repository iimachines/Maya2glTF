#pragma once

#include "spans.h"
#include "sceneTypes.h"

inline GLTF::Accessor::Type getAccessorType(const int dimension)
{
	// HACK: We assume SCALAR == 0 here...
	const auto type = static_cast<GLTF::Accessor::Type>(dimension - 1);
	return type;
}

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

	return contiguousAccessor(name,
		getAccessorType(dimension),
		GLTF::Constants::WebGL::FLOAT,
		target,
		data,
		1);
}

template<typename T>
std::unique_ptr<GLTF::Accessor> contiguousElementAccessor(
	const Semantic::Kind semantic,
	const ShapeIndex& shapeIndex,
	const gsl::span<T>& data)
{
	return contiguousAccessor(name(semantic),
		getAccessorType(dimension(semantic, shapeIndex)),
		GLTF::Constants::WebGL::FLOAT,
		GLTF::Constants::WebGL::ARRAY_BUFFER,
		reinterpret_span<float>(data),
		dimension(semantic, shapeIndex));
}
