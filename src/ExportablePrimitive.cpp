#include "externals.h"
#include "MeshRenderables.h"
#include "ExportablePrimitive.h"
#include "ExportableResources.h"
#include "accessors.h"
#include "Arguments.h"
#include "MayaException.h"

using namespace GLTF::Constants;
using namespace coveo::linq;

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

ExportablePrimitive::ExportablePrimitive(
	const VertexBuffer& vertexBuffer,
	ExportableResources& resources)
{
	CONSTRUCTOR_BEGIN();

	glPrimitive.mode = GLTF::Primitive::TRIANGLES;

	auto& vertexIndices = vertexBuffer.indices;

	if (resources.arguments().force32bitIndices ||
		vertexBuffer.maxIndex() > std::numeric_limits<uint16>::max())
	{
		// Use 32-bit indices
		glIndices = contiguousAccessor("indices", GLTF::Accessor::Type::SCALAR, WebGL::UNSIGNED_INT, WebGL::ELEMENT_ARRAY_BUFFER, span(vertexIndices), 1);
		glPrimitive.indices = glIndices.get();
	}
	else
	{
		// Use 16-bit indices
		std::vector<uint16> shortIndices(vertexIndices.size());
		std::copy(vertexIndices.begin(), vertexIndices.end(), shortIndices.begin());
		glIndices = contiguousAccessor("indices", GLTF::Accessor::Type::SCALAR, WebGL::UNSIGNED_SHORT, WebGL::ELEMENT_ARRAY_BUFFER, span(shortIndices), 1);
		glPrimitive.indices = glIndices.get();
	}

	auto componentsPerShapeIndex
		= from(vertexBuffer.componentsMap)
		| group_by([](auto& pair) { return pair.first.shapeIndex; })
		| to_vector();

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

	const auto mainShapeSemanticSet = resources.arguments().meshPrimitiveAttributes;
	const auto blendShapeSemanticSet = mainShapeSemanticSet & 
		MeshPrimitiveAttributeSet 
		{ 
			1 << Semantic::POSITION | 
			1 << Semantic::NORMAL | 
			1 << Semantic::TANGENT 
		};

	// Extract main shape vertices
	// TODO: Derived blend shape deltas!
	for (auto && group: componentsPerShapeIndex)
	{
		const auto shapeIndex = group.first;
		if (shapeIndex == 0)
		{
			for (auto && pair : group.second) 
			{
				auto& slot = pair.first;
				if (mainShapeSemanticSet.test(slot.semantic))
				{
					auto accessor = contiguousElementAccessor(slot.semantic, slot.shapeIndex, span(pair.second));
					glPrimitive.attributes[glTFattributeName(slot.semantic, slot.setIndex)] = accessor.get();
					glAccessors.emplace_back(std::move(accessor));
				}
			}
		}
		else
		{
			auto& glTarget = glTargetTable.at(shapeIndex - 1);

			for (auto && pair : group.second)
			{
				auto& slot = pair.first;
				if (blendShapeSemanticSet.test(slot.semantic))
				{
					auto accessor = contiguousElementAccessor(slot.semantic, slot.shapeIndex, span(pair.second));
					glTarget->attributes[glTFattributeName(slot.semantic, slot.setIndex)] = accessor.get();
					glAccessors.emplace_back(std::move(accessor));
				}
			}
		}
	}

	CONSTRUCTOR_END();
}

ExportablePrimitive::ExportablePrimitive(
	const VertexBuffer& vertexBuffer, 
	ExportableResources& resources,
	const Semantic::Kind debugSemantic,
	const int debugShapeIndex,
	const double debugLineLength,
	const Color debugLineColor)
{
	glPrimitive.mode = GLTF::Primitive::LINES;

	const auto positionSlot = VertexSlot(0, Semantic::POSITION, 0);
	const auto vectorSlot = VertexSlot(0, debugSemantic, 0);
	const auto positions = reinterpret_span<Position>(vertexBuffer.componentsMap.at(positionSlot));
	const auto vectorComponents = vertexBuffer.componentsMap.at(vectorSlot);
	const auto vectorDimension = dimension(debugSemantic, debugShapeIndex);
	const auto lineCount = positions.size();
	const auto elementCount = lineCount * 2;
	std::vector<uint16> lineIndices(elementCount);
	std::vector<Position> linePoints(elementCount);
	std::vector<Color> lineColors(elementCount);

	iota(lineIndices.begin(), lineIndices.end(), 0);
	fill(lineColors.begin(), lineColors.end(), debugLineColor);

	// Add a line from each point
	const float length = static_cast<float>(debugLineLength);
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

	auto pointAccessor = contiguousElementAccessor(Semantic::Kind::POSITION, 0, span(linePoints));
	glPrimitive.attributes[glTFattributeName(Semantic::Kind::POSITION, 0)] = pointAccessor.get();
	glAccessors.emplace_back(move(pointAccessor));

	auto colorAccessor = contiguousElementAccessor(Semantic::Kind::COLOR, 0, span(lineColors));
	glPrimitive.attributes[glTFattributeName(Semantic::Kind::COLOR, 0)] = colorAccessor.get();
	glAccessors.emplace_back(move(colorAccessor));
}

ExportablePrimitive::~ExportablePrimitive() = default;

