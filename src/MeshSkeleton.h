#pragma once

#include "macros.h"
#include "sceneTypes.h"
#include "MeshSemantics.h"
#include <ostream>
#include "dump.h"

class Arguments;
class MeshIndices;
class ExportableScene;
class ExportableNode;

class VertexJointAssignment
{
public:
	int jointIndex;
	float jointWeight;

	VertexJointAssignment(const int jointIndex, const float jointWeight)
		: jointIndex(jointIndex),
		  jointWeight(jointWeight)
	{
	}

	friend std::ostream& operator<<(std::ostream& os, const VertexJointAssignment& obj)
	{
		return os << "[" << obj.jointIndex << ", " << std::setprecision(3) << obj.jointWeight << "]";
	}

	DEFAULT_COPY_MOVE_ASSIGN_CTOR_DTOR(VertexJointAssignment);
};

// Per vertex, the joint assignments
typedef std::vector<gsl::span<const VertexJointAssignment>> VertexJointAssignmentTable;

struct MeshJoint
{
	ExportableNode* node;
	MMatrix inverseBindMatrix;

	MeshJoint(ExportableNode* node, const MMatrix& inverseBindMatrix)
		: node(node)
		, inverseBindMatrix(inverseBindMatrix)
	{
	}

	DEFAULT_COPY_MOVE_ASSIGN_DTOR(MeshJoint);
};

typedef std::vector<MeshJoint> MeshJoints;

class MeshSkeleton
{
public:
	MeshSkeleton(ExportableScene& scene, const ExportableNode& node, const MFnMesh& mesh);
	virtual ~MeshSkeleton();

	void dump(class IndentableStream& out, const std::string& name) const;

	bool isEmpty() const { return m_maxVertexJointAssignmentCount == 0; }

	const MeshJoints& joints() const { return m_joints; }
	
	const VertexJointAssignmentTable& vertexJointAssignments() const { return m_vertexJointAssignmentsTable; }

	size_t maxVertexJointAssignmentCount() const { return m_maxVertexJointAssignmentCount; }

	size_t vertexJointAssignmentSetCount() const;

private:
	DISALLOW_COPY_MOVE_ASSIGN(MeshSkeleton);

	MeshJoints m_joints;

	std::vector<VertexJointAssignment> m_vertexJointAssignmentsVector;
	VertexJointAssignmentTable m_vertexJointAssignmentsTable;
	size_t m_maxVertexJointAssignmentCount;

	static MObject tryExtractSkinCluster(const MFnMesh& fnMesh, const MSelectionList& ignoredDeformers);
};
