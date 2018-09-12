#include "externals.h"
#include "MeshRenderables.h"
#include "ExportablePrimitive.h"
#include "ExportableResources.h"
#include "accessors.h"
#include "Arguments.h"
#include "MayaException.h"

using namespace GLTF::Constants;
using namespace coveo::linq;

ExportablePrimitive::ExportablePrimitive(
		const VertexBuffer &vertexBuffer,
		ExportableResources &resources,
		ExportableMaterial *material)
{
	auto &args = resources.arguments();

	glPrimitive.mode = GLTF::Primitive::TRIANGLES;
	glPrimitive.material = material->glMaterial();

	auto &vertexIndices = vertexBuffer.indices;

	if (args.force32bitIndices ||
			vertexBuffer.maxIndex() > std::numeric_limits<uint16_t>::max())
	{
		// Use 32-bit indices
		glIndices = contiguousAccessor("indices", GLTF::Accessor::Type::SCALAR, WebGL::UNSIGNED_INT, WebGL::ELEMENT_ARRAY_BUFFER, span(vertexIndices), 1);
		glPrimitive.indices = glIndices.get();
	}
	else
	{
		// Use 16-bit indices
		std::vector<uint16_t> shortIndices(vertexIndices.size());
		std::copy(vertexIndices.begin(), vertexIndices.end(), shortIndices.begin());
		glIndices = contiguousAccessor("indices", GLTF::Accessor::Type::SCALAR, WebGL::UNSIGNED_SHORT, WebGL::ELEMENT_ARRAY_BUFFER, span(shortIndices), 1);
		glPrimitive.indices = glIndices.get();
	}

	auto componentsPerShapeIndex = from(vertexBuffer.componentsMap) | group_by([](auto &pair) { return pair.first.shapeIndex; }) | to_vector();

	// Allocate a glTF morph-target for each blend-shape
	const auto shapeCount = componentsPerShapeIndex.size();
	if (shapeCount > 1)
	{
		glTargetTable.reserve(shapeCount - 1);
		for (size_t i = 1; i < shapeCount; ++i)
		{
			auto glTarget = std::make_unique<GLTF::Primitive::Target>();
			glPrimitive.targets.emplace_back(glTarget.get());
			glTargetTable.emplace_back(move(glTarget));
		}
	}

	auto mainShapeSemanticSet = args.meshPrimitiveAttributes;

	// Don't add texture coordinates if no textures are used, if option is enabled
	if (args.excludeUnusedTexcoord && !material->hasTextures())
		mainShapeSemanticSet.set(Semantic::TEXCOORD, false);

	const auto blendShapeSemanticSet = args.blendPrimitiveAttributes & mainShapeSemanticSet;

	for (auto &&group : componentsPerShapeIndex)
	{
		const auto shapeIndex = group.first;

		auto &glAttributes = shapeIndex.isMainShapeIndex() ? glPrimitive.attributes : glTargetTable.at(shapeIndex.targetIndex())->attributes;
		auto &semanticSet = shapeIndex.isMainShapeIndex() ? mainShapeSemanticSet : blendShapeSemanticSet;

		for (auto &&pair : group.second)
		{
			auto &slot = pair.first;
			if (semanticSet.test(slot.semantic))
			{
				auto accessor = contiguousElementAccessor(slot.semantic, slot.shapeIndex, pair.second);
				glAttributes[glAttributeName(slot.semantic, slot.setIndex)] = accessor.get();
				glAccessors.emplace_back(std::move(accessor));
			}
		}
	}
}

ExportablePrimitive::ExportablePrimitive(
		const VertexBuffer &vertexBuffer,
		ExportableResources &resources,
		const Semantic::Kind debugSemantic,
		const ShapeIndex &debugShapeIndex,
		const double debugLineLength,
		const Color debugLineColor)
{
	glPrimitive.mode = GLTF::Primitive::LINES;

	const auto positionSlot = VertexSlot(ShapeIndex::main(), Semantic::POSITION, 0);
	const auto vectorSlot = VertexSlot(ShapeIndex::main(), debugSemantic, 0);
	const auto positions = reinterpret_span<Position>(vertexBuffer.componentsMap.at(positionSlot));
	const auto vectorComponents = reinterpret_span<float>(vertexBuffer.componentsMap.at(vectorSlot));
	const auto vectorDimension = dimension(debugSemantic, debugShapeIndex);
	const auto lineCount = positions.size();
	const auto elementCount = lineCount * 2;
	std::vector<uint16_t> lineIndices(elementCount);
	std::vector<Position> linePoints(elementCount);
	std::vector<Color> lineColors(elementCount);

	iota(lineIndices.begin(), lineIndices.end(), 0);
	fill(lineColors.begin(), lineColors.end(), debugLineColor);

	// Add a line from each point
	const auto length = static_cast<float>(debugLineLength);
	for (auto lineIndex = 0; lineIndex < lineCount; ++lineIndex)
	{
		const auto offset = lineIndex * 2;

		const auto vectorOffset = vectorDimension * lineIndex;
		const auto vx = vectorComponents[vectorOffset + 0];
		const auto vy = vectorComponents[vectorOffset + 1];
		const auto vz = vectorComponents[vectorOffset + 2];

		auto point = positions[lineIndex];
		linePoints[offset + 0] = point;

		point[0] += vx * length;
		point[1] += vy * length;
		point[2] += vz * length;
		linePoints[offset + 1] = point;
	}

	glIndices = contiguousAccessor("indices", GLTF::Accessor::Type::SCALAR, WebGL::UNSIGNED_SHORT, WebGL::ELEMENT_ARRAY_BUFFER, span(lineIndices), 1);
	glPrimitive.indices = glIndices.get();

	auto pointAccessor = contiguousElementAccessor(Semantic::Kind::POSITION, ShapeIndex::main(), reinterpret_span<byte>(linePoints));
	glPrimitive.attributes[glAttributeName(Semantic::Kind::POSITION, 0)] = pointAccessor.get();
	glAccessors.emplace_back(std::move(pointAccessor));

	auto colorAccessor = contiguousElementAccessor(Semantic::Kind::COLOR, ShapeIndex::main(), reinterpret_span<byte>(lineColors));
	glPrimitive.attributes[glAttributeName(Semantic::Kind::COLOR, 0)] = colorAccessor.get();
	glAccessors.emplace_back(std::move(colorAccessor));
}

ExportablePrimitive::~ExportablePrimitive() = default;

std::string ExportablePrimitive::glAttributeName(Semantic::Kind s, SetIndex setIndex)
{
	auto &map = m_glAttributeIndexMaps[s];
	auto it = map.find(setIndex);
	auto glSetIndex = it == map.end() ? (map[setIndex] = SetIndex(map.size())) : it->second;

	// NOTE: Although Maya has multiple tangent sets, glTF only accepts one.
	// Need to dig deeper to understand this correctly.
	switch (s)
	{
	case Semantic::POSITION:
		return std::string("POSITION");
	case Semantic::NORMAL:
		return std::string("NORMAL");
	case Semantic::TANGENT:
		return std::string("TANGENT");
	case Semantic::COLOR:
		return std::string("COLOR_") + std::to_string(glSetIndex);
	case Semantic::TEXCOORD:
		return std::string("TEXCOORD_") + std::to_string(glSetIndex);
	case Semantic::WEIGHTS:
		return std::string("WEIGHTS_") + std::to_string(glSetIndex);
	case Semantic::JOINTS:
		return std::string("JOINTS_") + std::to_string(glSetIndex);
	default:
		assert(false);
		return "UNKNOWN";
	}
}
