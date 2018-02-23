#include "externals.h"
#include "MeshRenderables.h"
#include "ExportablePrimitive.h"
#include "ExportableResources.h"
#include "ExportableMaterial.h"
#include "spans.h"
#include "Arguments.h"

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

ExportablePrimitive::ExportablePrimitive(
	const VertexBuffer& vertexBuffer,
	ExportableResources& resources)
{
	glPrimitive.mode = GLTF::Primitive::TRIANGLES;

	auto& vertexIndices = vertexBuffer.indices;

	if (resources.arguments().force32bitIndices ||
		vertexBuffer.maxIndex() > std::numeric_limits<uint16>::max())
	{
		// Use 32-bit indices
		const auto spanIndices = span(vertexIndices);
		const auto data = makeBuffer(spanIndices);
		glIndices = createAccessor(GLTF::Accessor::Type::SCALAR, WebGL::UNSIGNED_INT, WebGL::ELEMENT_ARRAY_BUFFER, data);
		glPrimitive.indices = glIndices.get();
	}
	else
	{
		// Use 16-bit indices
		std::vector<uint16> shortIndices(vertexIndices.size());
		std::copy(vertexIndices.begin(), vertexIndices.end(), shortIndices.begin());
		const auto spanIndices = reinterpret_span<uint8>(span(shortIndices));
		const auto data = makeBuffer(spanIndices);

		glIndices = createAccessor(GLTF::Accessor::Type::SCALAR, WebGL::UNSIGNED_SHORT, WebGL::ELEMENT_ARRAY_BUFFER, data);
		glPrimitive.indices = glIndices.get();
	}

	// Extract main shape vertices
	// TODO: Derived blend shape deltas!
	for (auto && pair: vertexBuffer.componentsMap)
	{
		const auto& slot = pair.first;
		if (slot.shapeIndex == 0)
		{
			const auto& components = pair.second;
			const auto data = makeBuffer(gsl::make_span(components));
			auto accessor = createAccessor(slot.semantic, data);
			glPrimitive.attributes[glTFattributeName(slot.semantic, slot.setIndex)] = accessor.get();
			glAccessorTable[slot.semantic].emplace_back(move(accessor));
		}
	}
}

ExportablePrimitive::ExportablePrimitive(
	const VertexBuffer& vertexBuffer, 
	ExportableResources& resources,
	const Semantic::Kind debugSemantic,
	const double debugLineLength)
{
	glPrimitive.mode = GLTF::Primitive::LINES;

	const auto positionSlot = VertexSlot(0, Semantic::POSITION, 0);
	const auto vectorSlot = VertexSlot(0, debugSemantic, 0);
	const auto positions = reinterpret_span<Position>(vertexBuffer.componentsMap.at(positionSlot));
	const auto vectorComponents = vertexBuffer.componentsMap.at(vectorSlot);
	const auto vectorDimension = Semantic::dimension(debugSemantic);
	const auto lineCount = positions.size();

	const auto lineIndices = allocBuffer<uint16>(lineCount * 2);
	const auto linePoints = allocBuffer<Position>(lineCount * 2);

	// Add a line from each point
	float length = static_cast<float>(debugLineLength);
	for (auto lineIndex = 0; lineIndex < lineCount; ++lineIndex)
	{
		const auto offset = lineIndex * 2;
		lineIndices[offset + 0] = offset + 0;
		lineIndices[offset + 1] = offset + 1;

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

	const auto indexBuffer = makeBuffer(lineIndices);
	glIndices = createAccessor(GLTF::Accessor::Type::SCALAR, WebGL::UNSIGNED_INT, WebGL::ELEMENT_ARRAY_BUFFER, indexBuffer);
	glPrimitive.indices = glIndices.get();

	const auto pointBuffer = makeBuffer(linePoints);
	auto accessor = createAccessor(Semantic::Kind::POSITION, pointBuffer);
	glPrimitive.attributes[glTFattributeName(Semantic::Kind::POSITION, 0)] = accessor.get();
	glAccessorTable[vectorSlot.semantic].emplace_back(move(accessor));
}

ExportablePrimitive::~ExportablePrimitive() = default;

