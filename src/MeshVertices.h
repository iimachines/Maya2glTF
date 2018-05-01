#pragma once

#include "macros.h"
#include "sceneTypes.h"
#include "MeshSemantics.h"
#include "spans.h"
#include <ostream>

class VertexComponents
{
public:
	Component::Type type;

	const gsl::span<const byte>& bytes() const { return m_data; }
	gsl::span<const float> floats() const { return reinterpret_span<float>(m_data); }
	gsl::span<const ushort> shorts() const { return reinterpret_span<ushort>(m_data); }

	explicit VertexComponents(const gsl::span<const float>& fs)
		: type(Component::FLOAT)
		, m_data(reinterpret_span<byte>(fs))
	{
	}

	explicit VertexComponents(const gsl::span<const ushort>& ns)
		: type(Component::USHORT)
		, m_data(reinterpret_span<byte>(ns))
	{
	}

	VertexComponents subspan(const size_t offset, const size_t count) const
	{
		switch (type)
		{
		case Component::FLOAT:
			return VertexComponents(floats().subspan(offset, count));
		case Component::USHORT:
			return VertexComponents(shorts().subspan(offset, count));
		default:
			throw std::runtime_error("Invalid component type");
		}
	}

	friend bool operator==(const VertexComponents& lhs, const VertexComponents& rhs)
	{
		return lhs.type == rhs.type
			&& lhs.m_data == rhs.m_data;
	}

	friend bool operator!=(const VertexComponents& lhs, const VertexComponents& rhs)
	{
		return !(lhs == rhs);
	}

	bool empty() const { return m_data.empty(); }

	DEFAULT_COPY_MOVE_ASSIGN_DTOR(VertexComponents);

private:
	gsl::span<const byte> m_data;
};

template<typename T>
inline VertexComponents floats(gsl::span<T> span)
{
	return VertexComponents(reinterpret_span<float>(span));
}

template<typename T>
inline VertexComponents shorts(gsl::span<T> span)
{
	return VertexComponents(reinterpret_span<ushort>(span));
}

typedef std::vector<VertexComponents> VertexElementsPerSetIndex;

typedef std::array<VertexElementsPerSetIndex, Semantic::COUNT> VertexElementsPerSetIndexTable;

inline VertexComponents componentsAt(const VertexComponents& elements, const size_t vertexIndex, const Semantic::Kind semantic, const ShapeIndex& shapeIndex)
{
	const auto count = dimension(semantic, shapeIndex);
	return elements.subspan(vertexIndex*count, count);
}

class Arguments;
class MeshIndices;
class ExportableNode;

class MeshVertices
{
public:
	MeshVertices(const MeshIndices& meshIndices, const MeshSkeleton* meshSkeleton, const MFnMesh& mesh, ShapeIndex shapeIndex, const ExportableNode& node, const Arguments& args);
	virtual ~MeshVertices();

	const ShapeIndex shapeIndex;

	const VertexElementsPerSetIndexTable& table() const { return m_table; }

	void dump(class IndentableStream& out, const std::string& name) const;

	const VertexComponents& vertexElementComponentsAt(const size_t semanticIndex, const size_t setIndex) const
	{
		return m_table.at(semanticIndex).at(setIndex);
	}

private:
	friend class MeshShape;

	PositionVector m_positions;
	NormalVector m_normals;

	std::map<SetIndex, FloatVector> m_tangentSets;
	std::map<SetIndex, TexCoordVector> m_uvSets;
	std::map<SetIndex, ColorVector> m_colorSets;
	std::map<SetIndex, JointWeightsVector> m_jointWeights;
	std::map<SetIndex, JointIndicesVector> m_jointIndices;

	VertexElementsPerSetIndexTable m_table;

	DISALLOW_COPY_MOVE_ASSIGN(MeshVertices);
};
