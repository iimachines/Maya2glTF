#pragma once
#include "basicTypes.h"
#include <ostream>

/** Index of a mesh shape, 0 means the base shape, 1 the first blend-shape target */
class ShapeIndex
{
public:
	static ShapeIndex main() { return ShapeIndex(0); }
	static ShapeIndex target(const int index) { return ShapeIndex(index + 1); }
	static ShapeIndex shape(const int index) { return ShapeIndex(index); }
	static ShapeIndex invalid() { return ShapeIndex(-1); }

	DEFAULT_COPY_MOVE_ASSIGN_DESTRUCT(ShapeIndex);

	friend size_t hash_value(const ShapeIndex& obj)
	{
		size_t seed = 0x26DFB62C;
		seed ^= (seed << 6) + (seed >> 2) + 0x3C2E6B88 + static_cast<size_t>(obj.m_value);
		return seed;
	}

	friend bool operator==(const ShapeIndex& lhs, const ShapeIndex& rhs)
	{
		return lhs.m_value == rhs.m_value;
	}

	friend bool operator!=(const ShapeIndex& lhs, const ShapeIndex& rhs)
	{
		return !(lhs == rhs);
	}


	friend bool operator<(const ShapeIndex& lhs, const ShapeIndex& rhs)
	{
		return lhs.m_value < rhs.m_value;
	}

	friend bool operator<=(const ShapeIndex& lhs, const ShapeIndex& rhs)
	{
		return !(rhs < lhs);
	}

	friend bool operator>(const ShapeIndex& lhs, const ShapeIndex& rhs)
	{
		return rhs < lhs;
	}

	friend bool operator>=(const ShapeIndex& lhs, const ShapeIndex& rhs)
	{
		return !(lhs < rhs);
	}


	friend std::ostream& operator<<(std::ostream& os, const ShapeIndex& obj)
	{
		return os << obj.m_value;
	}

	int arrayIndex() const { assert(m_value >= 0); return m_value; }
	int targetIndex() const { assert(m_value > 0); return static_cast<int>(m_value - 1); }

	bool isMainShapeIndex() const { return m_value == 0; }
	bool isBlendShapeIndex() const { return m_value > 0; }

private:
	explicit ShapeIndex(const int value) : m_value(value) {};

	int m_value;
};
