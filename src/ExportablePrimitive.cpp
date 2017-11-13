#include "externals.h"
#include "MayaException.h"
#include "Mesh.h"
#include "MeshRenderable.h"
#include "ExportablePrimitive.h"
#include "spans.h"

ExportablePrimitive::ExportablePrimitive(const MeshRenderable& renderable)
	: glBuffer(nullptr, 0)
	, glView(0, 0, &glBuffer)
{
	glPrimitive.mode = GLTF::Primitive::TRIANGLES;

	auto& renderableIndices = renderable.indices();
	auto& renderableTable = renderable.table();

	auto spanIndices = reinterpret_span<uint8>(span(renderableIndices));
	m_data.insert(m_data.end(), spanIndices.begin(), spanIndices.end());

	glIndices = std::make_unique<GLTF::Accessor>(
		GLTF::Accessor::Type::SCALAR, GLTF::Constants::WebGL::UNSIGNED_INT, 0, 
		static_cast<int>(renderableIndices.size()), &glView);

	glPrimitive.indices = glIndices.get();

	for (int semanticIndex = 0; semanticIndex < Semantic::COUNT; ++semanticIndex)
	{
		const auto semanticKind = Semantic::from(semanticIndex);
		const auto& componentsPerSetIndex = renderableTable.at(semanticIndex);

		for (int setIndex = 0; setIndex < componentsPerSetIndex.size(); ++setIndex)
		{
			const auto& renderableComponents = componentsPerSetIndex.at(setIndex);

			auto accessor = createAccessor(semanticKind, static_cast<int>(m_data.size()), static_cast<int>(renderableComponents.size()));
			glPrimitive.attributes[attributeName(semanticKind, setIndex)] = accessor.get();
			glAccessorTable[semanticIndex].emplace_back(move(accessor));

			auto spanComponents = reinterpret_span<uint8>(span(renderableComponents));
			m_data.insert(m_data.end(), spanComponents.begin(), spanComponents.end());

			++setIndex;
		}
	}

	glBuffer.data = &m_data[0];
	glBuffer.byteLength = static_cast<int>(m_data.size());
	glView.byteLength = glBuffer.byteLength;
}

ExportablePrimitive::~ExportablePrimitive()
{
}

std::unique_ptr<GLTF::Accessor> ExportablePrimitive::createAccessor(const Semantic::Kind semantic, const int offset, const int count)
{
	switch (semantic)
	{
	case Semantic::POSITION:
		return std::make_unique<GLTF::Accessor>(GLTF::Accessor::Type::VEC4, GLTF::Constants::WebGL::FLOAT, offset, count, &glView);
	case Semantic::NORMAL:
		return std::make_unique<GLTF::Accessor>(GLTF::Accessor::Type::VEC3, GLTF::Constants::WebGL::FLOAT, offset, count, &glView);
	case Semantic::COLOR:
		return std::make_unique<GLTF::Accessor>(GLTF::Accessor::Type::VEC4, GLTF::Constants::WebGL::FLOAT, offset, count, &glView);
	case Semantic::TEXCOORD:
		return std::make_unique<GLTF::Accessor>(GLTF::Accessor::Type::VEC2, GLTF::Constants::WebGL::FLOAT, offset, count, &glView);
	default:
		assert(false);
		return nullptr;
	}
}

