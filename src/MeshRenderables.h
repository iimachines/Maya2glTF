#pragma once

#include "sceneTypes.h"
#include "hashers.h"
#include "dump.h"
#include "MeshShape.h"

class Arguments;

typedef int VertexIndex;

// TODO: We currently do not support more than 64 slots per vertex.
typedef uint64_t VertexSlotUsage;

struct VertexSignature
{
	ShaderIndex shaderIndex;
	VertexSlotUsage slotUsage;

	/**
	* For each semantic/set-index pair, per shader, for both main mesh and blend-shapes,
	* a bit to indicate if a vertex element has this semantic/set-index
	* For example, some of the vertices of a Maya mesh might not have UVs, colors, etc...
	* TODO: Simpify this!
	*/

	explicit VertexSignature(const ShaderIndex shaderIndex, const VertexSlotUsage slotUsage)
		: shaderIndex(shaderIndex)
		, slotUsage(slotUsage)
	{
	}

	DEFAULT_COPY_MOVE_ASSIGN_DESTRUCT(VertexSignature);
	
	friend bool operator==(const VertexSignature& lhs, const VertexSignature& rhs)
	{
		return lhs.shaderIndex == rhs.shaderIndex
			&& lhs.slotUsage == rhs.slotUsage;
	}

	friend bool operator!=(const VertexSignature& lhs, const VertexSignature& rhs)
	{
		return !(lhs == rhs);
	}

	friend bool operator<(const VertexSignature& lhs, const VertexSignature& rhs)
	{
		return lhs.shaderIndex < rhs.shaderIndex && lhs.slotUsage < rhs.slotUsage;
	}

	friend bool operator<=(const VertexSignature& lhs, const VertexSignature& rhs)
	{
		return !(rhs < lhs);
	}

	friend bool operator>(const VertexSignature& lhs, const VertexSignature& rhs)
	{
		return rhs < lhs;
	}

	friend bool operator>=(const VertexSignature& lhs, const VertexSignature& rhs)
	{
		return !(lhs < rhs);
	}

	friend std::size_t hash_value(const VertexSignature& obj)
	{
		std::size_t seed = 0x61BAB927;
		seed ^= (seed << 6) + (seed >> 2) + 0x79FBC802 + static_cast<std::size_t>(obj.shaderIndex);
		seed ^= (seed << 6) + (seed >> 2) + 0x5A1BB057 + static_cast<std::size_t>(obj.slotUsage);
		return seed;
	}

	friend std::ostream& operator <<(std::ostream& out, const VertexSignature& obj);
};

struct VertexSlot
{
	ShapeIndex shapeIndex;
	Semantic::Kind semantic;
	SetIndex setIndex;

	VertexSlot()
		: shapeIndex(ShapeIndex::invalid())
		, semantic(Semantic::Kind::INVALID)
		, setIndex(-1)
	{
	}

	VertexSlot(const ShapeIndex& shapeIndex, const Semantic::Kind semantic, const SetIndex setIndex)
		: shapeIndex(shapeIndex)
		, semantic(semantic)
		, setIndex(setIndex)
	{
	}

	DEFAULT_COPY_MOVE_ASSIGN_DESTRUCT(VertexSlot);

	friend std::ostream& operator <<(std::ostream& out, const VertexSlot& slot);

	friend bool operator==(const VertexSlot& lhs, const VertexSlot& rhs)
	{
		return lhs.shapeIndex == rhs.shapeIndex
			&& lhs.semantic == rhs.semantic
			&& lhs.setIndex == rhs.setIndex;
	}

	friend bool operator!=(const VertexSlot& lhs, const VertexSlot& rhs)
	{
		return !(lhs == rhs);
	}

	friend bool operator<(const VertexSlot& lhs, const VertexSlot& rhs)
	{
		if (lhs.shapeIndex < rhs.shapeIndex)
			return true;
		if (rhs.shapeIndex < lhs.shapeIndex)
			return false;
		if (lhs.semantic < rhs.semantic)
			return true;
		if (rhs.semantic < lhs.semantic)
			return false;
		return lhs.setIndex < rhs.setIndex;
	}

	friend bool operator<=(const VertexSlot& lhs, const VertexSlot& rhs)
	{
		return !(rhs < lhs);
	}

	friend bool operator>(const VertexSlot& lhs, const VertexSlot& rhs)
	{
		return rhs < lhs;
	}

	friend bool operator>=(const VertexSlot& lhs, const VertexSlot& rhs)
	{
		return !(lhs < rhs);
	}

	friend std::size_t hash_value(const VertexSlot& obj)
	{
		std::size_t seed = 0x7732D720;
		seed ^= (seed << 6) + (seed >> 2) + 0x6654736D + hash_value(obj.shapeIndex);
		seed ^= (seed << 6) + (seed >> 2) + 0x1BF620AC + static_cast<std::size_t>(obj.semantic);
		seed ^= (seed << 6) + (seed >> 2) + 0x54A5F37C + static_cast<std::size_t>(obj.setIndex);
		return seed;
	}

	size_t dimension() const
	{
		return Semantic::dimension(semantic, shapeIndex);
	}
};

struct VertexHashers
{
	std::size_t operator()(const VertexSlot& obj) const
	{
		return hash_value(obj);
	}

	std::size_t operator()(const VertexSignature& obj) const
	{
		return hash_value(obj);
	}
};

typedef std::vector<VertexSlot> VertexLayout;

typedef std::unordered_map<FloatVector, Index, CollectionHashers> VertexToIndexMapping;

// TODO: Use valarrays here?
typedef std::unordered_map<VertexSlot, FloatVector, VertexHashers> VertexComponentsMap;

struct VertexBuffer
{
	VertexToIndexMapping vertexToIndexMapping;
	IndexVector indices;
	VertexComponentsMap componentsMap;
	
	size_t maxIndex() const { return vertexToIndexMapping.size(); };

	friend std::ostream& operator <<(std::ostream& out, const VertexBuffer& obj);
};

typedef std::unordered_map<VertexSignature, VertexBuffer, VertexHashers> VertexBufferTable;

class MeshRenderables
{
public:
	MeshRenderables(
		InstanceIndex instanceIndex,
		const MeshShapes& meshShapes,
		const Arguments& args);

	~MeshRenderables() = default;

	const InstanceIndex instanceIndex;

	const VertexBufferTable& table() const { return m_table; }

protected:
	DISALLOW_COPY_MOVE_ASSIGN(MeshRenderables);
	VertexBufferTable m_table;
};
