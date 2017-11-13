#include "externals.h"
#include "MayaException.h"
#include "Mesh.h"
#include "MeshRenderable.h"
#include "ExportablePrimitive.h"
#include "spans.h"

using namespace GLTF::Constants;

ExportablePrimitive::ExportablePrimitive(const MeshRenderable& renderable)
{
	glPrimitive.mode = GLTF::Primitive::TRIANGLES;

	auto& renderableIndices = renderable.indices();
	auto& renderableTable = renderable.table();

	auto spanIndices = reinterpret_span<uint8>(span(renderableIndices));
	m_data.insert(m_data.end(), spanIndices.begin(), spanIndices.end());

	glIndices = std::make_unique<GLTF::Accessor>(
		GLTF::Accessor::Type::SCALAR, WebGL::UNSIGNED_INT,
		&m_data[0], static_cast<int>(renderableIndices.size()),
		WebGL::ELEMENT_ARRAY_BUFFER);

	glPrimitive.indices = glIndices.get();

	for (int semanticIndex = 0; semanticIndex < Semantic::COUNT; ++semanticIndex)
	{
		const auto semanticKind = Semantic::from(semanticIndex);
		const auto& componentsPerSetIndex = renderableTable.at(semanticIndex);
		const auto componentDimension = Semantic::dimension(semanticKind);

		for (int setIndex = 0; setIndex < componentsPerSetIndex.size(); ++setIndex)
		{
			const auto& renderableComponents = componentsPerSetIndex.at(setIndex);

			if (renderableComponents.size())
			{
				const int offset = static_cast<int>(m_data.size());
				const int count = static_cast<int>(renderableComponents.size() / componentDimension);

				auto spanComponents = reinterpret_span<uint8>(span(renderableComponents));
				m_data.insert(m_data.end(), spanComponents.begin(), spanComponents.end());

				auto accessor = createAccessor(semanticKind, offset, count);
				glPrimitive.attributes[attributeName(semanticKind, setIndex)] = accessor.get();
				glAccessorTable[semanticIndex].emplace_back(move(accessor));
			}
		}
	}
}

ExportablePrimitive::~ExportablePrimitive()
{
}

std::unique_ptr<GLTF::Accessor> ExportablePrimitive::createAccessor(const Semantic::Kind semantic, const int offset, const int count)
{
	auto data = &m_data[offset];

	switch (semantic)
	{
	case Semantic::POSITION:
		return std::make_unique<GLTF::Accessor>(GLTF::Accessor::Type::VEC3, WebGL::FLOAT, data, count, WebGL::ARRAY_BUFFER);
	case Semantic::NORMAL:
		return std::make_unique<GLTF::Accessor>(GLTF::Accessor::Type::VEC3, WebGL::FLOAT, data, count, WebGL::ARRAY_BUFFER);
	case Semantic::COLOR:
		return std::make_unique<GLTF::Accessor>(GLTF::Accessor::Type::VEC4, WebGL::FLOAT, data, count, WebGL::ARRAY_BUFFER);
	case Semantic::TEXCOORD:
		return std::make_unique<GLTF::Accessor>(GLTF::Accessor::Type::VEC2, WebGL::FLOAT, data, count, WebGL::ARRAY_BUFFER);
	default:
		assert(false);
		return nullptr;
	}
}

