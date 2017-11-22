#include "externals.h"
#include "Mesh.h"
#include "MayaException.h"
#include <any>

Mesh::Mesh(const MDagPath& dagPath) 
{
	MStatus status;

	const MFnMesh fnMesh(dagPath, &status);
	THROW_ON_FAILURE(status);

	m_shape = std::make_unique<MeshShape>(fnMesh, false);

	MObject blendShapeController = tryExtractBlendController(fnMesh);
	if (!blendShapeController.isNull())
	{
		m_blendShapes = std::make_unique<MeshBlendShapes>(blendShapeController);
	}

	auto instanceNumber = dagPath.instanceNumber(&status);
	THROW_ON_FAILURE(status);

	m_shapeCollection = std::make_unique<MeshShapeCollection>(*m_shape, m_blendShapes.get());

	m_renderables = std::make_unique<MeshRenderables>(instanceNumber, *m_shapeCollection);
}

Mesh::~Mesh()
{
}

void Mesh::dump(std::ostream& out, const std::string& name, const std::string& indent) const
{
	out << indent << quoted(name) << ": {" << endl;
	const auto subIndent = indent + "\t";

	m_shape->dump(out, "shape", subIndent);
	out << "," << endl;

	if (m_blendShapes)
	{
		m_blendShapes->dump(out, "blendShapes", subIndent);
		out << "," << endl;
	}

	//m_renderables->dump(cout, "renderables", subIndent);
	//cout << "," << endl;

	out << indent << "}" << endl;
}


MObject Mesh::tryExtractBlendController(const MFnMesh& fnMesh)
{
	MObject blendController;

	// Iterate upstream to find all the nodes that affect the mesh.
	MStatus status;
	MPlug plug = fnMesh.findPlug("inMesh", status);
	THROW_ON_FAILURE(status);

	if (plug.isConnected())
	{
		MItDependencyGraph dgIt(plug,
			MFn::kInvalid,
			MItDependencyGraph::kUpstream,
			MItDependencyGraph::kBreadthFirst,
			MItDependencyGraph::kNodeLevel,
			&status);

		THROW_ON_FAILURE(status);

		dgIt.disablePruningOnFilter();

		for (; !dgIt.isDone(); dgIt.next())
		{
			MObject thisNode = dgIt.thisNode();
			if (thisNode.hasFn(MFn::kBlendShape))
			{
				MFnBlendShapeDeformer fnController(thisNode, &status);

				if (status == MStatus::kSuccess)
				{
					if (blendController.isNull())
					{
						blendController = thisNode;
					}
					else
					{
						cerr << "maya2glTF: ignoring blend controller " << MFnDependencyNode(thisNode).name() << endl;
					}
				}
				else
				{
					cerr << "maya2glTF: node has " << MFnDependencyNode(thisNode).name() << endl;
				}
			}
		}
	}

	return blendController;
}
