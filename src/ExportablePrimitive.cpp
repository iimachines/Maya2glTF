#include "externals.h"
#include "MayaException.h"
#include "Mesh.h"
#include "MeshRenderable.h"
#include "ExportablePrimitive.h"
#include "spans.h"

ExportablePrimitive::ExportablePrimitive(const MeshRenderable& renderable)
	: buffer(nullptr, 0)
	, view(0, 0, &buffer)
{
	primitive.mode = GLTF::Primitive::TRIANGLES;

	auto& renderableIndices = renderable.indices();
	auto& renderableTable = renderable.table();

	MeshAccessorPerSetIndexTable tableOffsets;

	auto spanIndices = reinterpret_span<uint8>(span(renderableIndices));
	m_data.insert(m_data.end(), spanIndices.begin(), spanIndices.end());

	indices = std::make_unique<GLTF::Accessor>(
		GLTF::Accessor::Type::SCALAR, GLTF::Constants::WebGL::UNSIGNED_INT, 0, 
		static_cast<int>(renderableIndices.size()), &view);

	primitive.indices = indices.get();

	for (int semanticIndex = 0; semanticIndex < Semantic::COUNT; ++semanticIndex)
	{
		const auto semanticKind = Semantic::from(semanticIndex);
		const auto& componentsPerSetIndex = renderableTable.at(semanticIndex);

		for (int setIndex = 0; setIndex < componentsPerSetIndex.size(); ++setIndex)
		{
			const auto& renderableComponents = componentsPerSetIndex.at(setIndex);

			auto accessor = createAccessor(semanticKind, static_cast<int>(m_data.size()), static_cast<int>(renderableComponents.size()));
			primitive.attributes[attributeName(semanticKind, setIndex)] = accessor;

			tableOffsets[semanticIndex].emplace_back(accessor);

			auto spanComponents = reinterpret_span<uint8>(span(renderableComponents));
			m_data.insert(m_data.end(), spanComponents.begin(), spanComponents.end());

			++setIndex;
		}
	}

	buffer.data = &m_data[0];
	buffer.byteLength = static_cast<int>(m_data.size());
	view.byteLength = buffer.byteLength;
}

ExportablePrimitive::~ExportablePrimitive()
{
}
GLTF::Accessor* ExportablePrimitive::createAccessor(const Semantic::Kind semantic, const int offset, const int count)
{
	switch (semantic)
	{
	case Semantic::POSITION:
		return new GLTF::Accessor(GLTF::Accessor::Type::VEC4, GLTF::Constants::WebGL::FLOAT_VEC4, offset, count, &view);
	case Semantic::NORMAL:
		return new GLTF::Accessor(GLTF::Accessor::Type::VEC3, GLTF::Constants::WebGL::FLOAT_VEC3, offset, count, &view);
	case Semantic::COLOR:
		return new GLTF::Accessor(GLTF::Accessor::Type::VEC4, GLTF::Constants::WebGL::FLOAT_VEC4, offset, count, &view);
	case Semantic::TEXCOORD:
		return new GLTF::Accessor(GLTF::Accessor::Type::VEC2, GLTF::Constants::WebGL::FLOAT_VEC2, offset, count, &view);
	default:
		assert(false);
		return nullptr;
	}
}

