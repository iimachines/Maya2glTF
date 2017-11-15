#include "externals.h"
#include "MayaException.h"
#include "MeshRenderable.h"
#include "ExportablePrimitive.h"
#include "ExportableResources.h"
#include "ExportableMaterial.h"
#include "spans.h"

using namespace GLTF::Constants;

namespace Semantic
{
	inline std::string glTFattributeName(const Kind s, const int setIndex)
	{
		// NOTE: Although Maya has multiple tangent sets, glTW only accepts one. 
		// Need to dig deeper to understand this correctly.
		switch (s)
		{
		case POSITION:	return std::string("POSITION");
		case NORMAL:	return std::string("NORMAL");
		case TANGENT:	return std::string("TANGENT");
		case COLOR:		return std::string("COLOR_") + std::to_string(setIndex);
		case TEXCOORD:	return std::string("TEXCOORD_") + std::to_string(setIndex);
		default: assert(false); return "UNKNOWN";
		}
	}
}

ExportablePrimitive::ExportablePrimitive(const MeshRenderable& renderable, ExportableResources& resources)
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
				glPrimitive.attributes[glTFattributeName(semanticKind, setIndex)] = accessor.get();
				glAccessorTable[semanticIndex].emplace_back(move(accessor));
			}
		}
	}

	// Link material
	const auto material = resources.getMaterial(renderable.shaderGroup());
	if (material)
	{
		glPrimitive.material = material->glMaterial();
	}
}

ExportablePrimitive::~ExportablePrimitive()
{
}

std::unique_ptr<GLTF::Accessor> ExportablePrimitive::createAccessor(const Semantic::Kind semantic, const int offset, const int count)
{
	auto data = &m_data[offset];

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

	return std::make_unique<GLTF::Accessor>(type, WebGL::FLOAT, data, count, WebGL::ARRAY_BUFFER);
}

