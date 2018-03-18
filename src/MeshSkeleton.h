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

typedef std::vector<ExportableNode*> MeshJoints;

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

class MeshSkeleton
{
public:
	MeshSkeleton(ExportableScene& scene, const MFnMesh& mesh);
	virtual ~MeshSkeleton();

	void dump(class IndentableStream& out, const std::string& name) const;

	bool isEmpty() const { return m_maxVertexJointAssignmentCount == 0; }

	int rootJointIndex() const { }
	
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
