#include "externals.h"
#include "Mesh.h"
#include "MayaException.h"

Mesh::Mesh(const MDagPath& dagPath) 
{
	MStatus status;

	const MFnMesh fnMesh(dagPath, &status);
	THROW_ON_FAILURE(status);

	m_shape = std::make_unique<MeshShape>(fnMesh, false);

	auto instanceNumber = dagPath.instanceNumber(&status);
	THROW_ON_FAILURE(status);

	// Find blend shapes. The weights of shapes are added as extra semantics
	MObject blendShapeController = tryExtractBlendController(fnMesh);
	if (!blendShapeController.isNull())
	{
		m_blendShapes = std::make_unique<MeshBlendShapes>(blendShapeController);
	}

	m_shapeCollection = std::make_unique<MeshShapeCollection>(*m_shape, m_blendShapes.get());

	m_renderables = std::make_unique<MeshRenderables>(instanceNumber, *m_shapeCollection);
}

Mesh::~Mesh()
{
}

void Mesh::dump(const std::string& name, const std::string& indent) const
{
	cout << indent << quoted(name) << ": {" << endl;
	const auto subIndent = indent + "\t";

	m_shape->dump("shape", subIndent);
	cout << "," << endl;

	if (m_blendShapes)
	{
		m_blendShapes->dump("blendShapes", subIndent);
		cout << "," << endl;
	}

	//m_renderables->dump("renderables", subIndent);
	//cout << "," << endl;

	cout << indent << "}" << endl;
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
				if (blendController.isNull())
				{
					blendController = thisNode;
				}
				else
				{
					cerr << "maya2glTF: ignoring blend controller " << MFnDependencyNode(thisNode).name() << endl;
				}
			}
		}
	}

	return blendController;
}
