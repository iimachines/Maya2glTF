#include "externals.h"
#include "MeshSkeleton.h"
#include "MayaException.h"
#include "IndentableStream.h"
#include "Arguments.h"
#include "spans.h"
#include "ExportableScene.h"
#include "ExportableNode.h"

struct VertexJointAssignmentSlice
{
	size_t offset;
	size_t length;

	VertexJointAssignmentSlice(const size_t assignmentOffset, const size_t assignmentLength)
		: offset(assignmentOffset)
		, length(assignmentLength)
	{
	}

	DEFAULT_COPY_MOVE_ASSIGN_CTOR_DTOR(VertexJointAssignmentSlice);
};

void scaleTranslation(MMatrix& m, double s)
{
	double* t = m[3];
	t[0] *= s;
	t[1] *= s;
	t[2] *= s;
}

MeshSkeleton::MeshSkeleton(
	ExportableScene& scene, 
	const ExportableNode& node,
	const MFnMesh& mesh)
	: m_maxVertexJointAssignmentCount(0)
{
	MStatus status;

	auto& args = scene.arguments();

	MObject skin = args.skipSkinClusters 
	? MObject::kNullObj 
	: tryExtractSkinCluster(mesh, args.ignoreMeshDeformers);
	
	if (!skin.isNull())
	{
		MFnSkinCluster fnSkin(skin, &status);
		THROW_ON_FAILURE(status);

		// Gather all the joints
		MDagPathArray jointDagPaths;
		const auto jointCount = fnSkin.influenceObjects(jointDagPaths, &status);
		THROW_ON_FAILURE(status);

		m_joints.reserve(jointCount);

		const auto shapeDagPath = mesh.dagPath(&status);
		THROW_ON_FAILURE(status);

		auto meshMatrix = shapeDagPath.inclusiveMatrix(&status);
		THROW_ON_FAILURE(status);
		scaleTranslation(meshMatrix, args.scaleFactor);

		for (size_t index = 0; index < jointCount; ++index)
		{
			auto& jointDagPath = jointDagPaths[static_cast<unsigned int>(index)];
			auto* jointNode = scene.getNode(jointDagPath);
			auto jointMatrix = jointDagPath.inclusiveMatrix(&status);
			THROW_ON_FAILURE(status);
			scaleTranslation(jointMatrix, args.scaleFactor);

			const auto inverseJointMatrix = jointMatrix.inverse();

			MMatrix inverseBindMatrix = meshMatrix * inverseJointMatrix;

			if (inverseBindMatrix.isSingular())
			{
				cerr << prefix << "WARNING: Inverse bind matrix of joint '" << jointNode->name() << "' is singular!" << endl;
			}
			else if (!hasOrthogonalAxes(inverseBindMatrix))
			{
				cerr << prefix << "WARNING: Inverse bind matrix of joint '" << jointNode->name() << "' is not orthogonal!" << endl;
			}

			m_joints.emplace_back(jointNode, inverseBindMatrix);
		}

		// Gather all joint index/weights per vertex, sorted ascendingly by weight
		const auto meshDagPath = mesh.dagPath(&status);
		THROW_ON_FAILURE(status);

		MItGeometry iterGeom(meshDagPath, &status);
		THROW_ON_FAILURE(status);

		const auto numPoints = iterGeom.count();

		MFloatArray vertexWeights;
		unsigned int numWeights;

		// Build joint (index,weight) assignments
		// To avoid many memory allocations, we put all assignments in a flat vector.
		m_vertexJointAssignmentsVector.reserve(numPoints * 8);

		std::vector<VertexJointAssignmentSlice> slices(numPoints);

		std::vector<VertexJointAssignment> assignments;
		assignments.reserve(jointCount);

		for (; !iterGeom.isDone(); iterGeom.next())
		{
			const auto pointIndex = iterGeom.index(&status);
			THROW_ON_FAILURE(status);

			const MObject component = iterGeom.component(&status);
			THROW_ON_FAILURE(status);

			status = fnSkin.getWeights(meshDagPath, component, vertexWeights, numWeights);
			THROW_ON_FAILURE(status);

			assignments.resize(0);

			for (int jointIndex = 0; jointIndex < int(numWeights); ++jointIndex)
			{
				const float jointWeight = vertexWeights[jointIndex];
				if (std::abs(jointWeight) > 1e-6f)
				{
					assignments.emplace_back(jointIndex, jointWeight);
				}
			}

			// Sort weights from large to small.
			// TODO: Use insertion sort when adding the weights?
			std::sort(assignments.begin(), assignments.end(), [](auto &left, auto &right) {
				return left.jointWeight > right.jointWeight;
			});

			const auto assignmentsLength = assignments.size();
			const auto assignmentsOffset = m_vertexJointAssignmentsVector.size();
			std::copy(assignments.begin(), assignments.end(), std::back_inserter(m_vertexJointAssignmentsVector));

			slices[pointIndex] = VertexJointAssignmentSlice(assignmentsOffset, assignmentsLength);

			m_maxVertexJointAssignmentCount = std::max(assignmentsLength, m_maxVertexJointAssignmentCount);
		}

		std::cout << prefix << "Skin for mesh " << meshDagPath.partialPathName().asChar() << " will use " << m_maxVertexJointAssignmentCount << " weights per vertex" << endl;

		// The vector now contains all the assignments, and cannot be relocated anymore; lets construct the table of spans
		m_vertexJointAssignmentsTable.resize(numPoints);

		auto spans = span(m_vertexJointAssignmentsVector);

		for (int vertexIndex = 0; vertexIndex < numPoints; ++vertexIndex)
		{
			const auto& slice = slices.at(vertexIndex);
			m_vertexJointAssignmentsTable[vertexIndex] = spans.subspan(slice.offset, slice.length);
		}
	}
}

MeshSkeleton::~MeshSkeleton() = default;

void MeshSkeleton::dump(IndentableStream& out, const std::string& name) const
{
	out << quoted(name) << ": [" << endl << indent;

	JsonSeparator sepLine(",\n");

	out << std::fixed;

	for (auto& assignments : m_vertexJointAssignmentsTable)
	{
		JsonSeparator sepElem(", ");

		out << "[ ";

		for (auto& assignment : assignments)
		{
			out << sepElem << assignment;
		}

		out << " ]";

		out << sepLine;
	}

	out << endl << undent << "]";
}

size_t MeshSkeleton::vertexJointAssignmentSetCount() const
{
	const auto vertexJointAssignmentComponentCount = maxVertexJointAssignmentCount();
	const auto vertexJointAssignmentElementSize = array_size<JointIndices>::size;
	const auto vertexJointAssignmentSetCount = (vertexJointAssignmentComponentCount + vertexJointAssignmentElementSize - 1) / vertexJointAssignmentElementSize;
	return vertexJointAssignmentSetCount;
}

MObject MeshSkeleton::tryExtractSkinCluster(const MFnMesh& fnMesh, const MSelectionList& ignoredDeformers)
{
	MStatus status;
	MObject cluster;

	const auto meshObject = fnMesh.object(&status);
	THROW_ON_FAILURE(status);

	const auto meshName = fnMesh.name(&status);
	THROW_ON_FAILURE(status);

	for (MItDependencyNodes depNodeIt(MFn::kSkinClusterFilter);
		!depNodeIt.isDone();
		depNodeIt.next())
	{
		MObject thisNode = depNodeIt.item(&status);
		THROW_ON_FAILURE(status);

		MFnSkinCluster fnSkinCluster(thisNode, &status);
		THROW_ON_FAILURE(status);

		const auto thisName = MFnDependencyNode(thisNode).name(&status);
		THROW_ON_FAILURE(status);

		if (ignoredDeformers.hasItem(thisNode))
		{
			cout << prefix << "Ignoring skin cluster" << thisName << endl;
		}
		else 
		{
			const auto geometryCount = fnSkinCluster.numOutputConnections(&status);
			THROW_ON_FAILURE(status);

			for (auto geometryIndex = 0U; geometryIndex < geometryCount; ++geometryIndex)
			{
				const auto shapeIndex = fnSkinCluster.indexForOutputConnection(geometryIndex, &status);
				THROW_ON_FAILURE(status);

				const auto shapeObject = fnSkinCluster.outputShapeAtIndex(shapeIndex, &status);
				THROW_ON_FAILURE(status);

				if (shapeObject == meshObject)
				{
					if (cluster.isNull())
					{
						cerr << prefix << "Found skin cluster " << thisName << " for mesh " << meshName << endl;
						cluster = thisNode;
					}
					else
					{
						cerr << prefix << "Only a single skin cluster is supported, skipping " << thisName << " for mesh " << meshName << endl;
					}
				}
			}
		}
	}

	if (cluster.isNull())
	{
		cerr << prefix << meshName << " is not skinned" << endl;
	}

	return cluster;
}
