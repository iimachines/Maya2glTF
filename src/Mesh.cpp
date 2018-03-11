#include "externals.h"
#include "Mesh.h"
#include "MayaException.h"
#include "Arguments.h"

Mesh::Mesh(const MDagPath& dagPath, const Arguments& args)
{
	CONSTRUCTOR_BEGIN();

	MStatus status;

	const MFnMesh fnMesh(dagPath, &status);
	THROW_ON_FAILURE(status);

	m_shape = std::make_unique<MeshShape>(fnMesh, args, false);

	MObject blendShapeController = tryExtractBlendController(fnMesh);
	if (!blendShapeController.isNull())
	{
		m_blendShapes = std::make_unique<MeshBlendShapes>(blendShapeController, args);
	}

	auto instanceNumber = dagPath.instanceNumber(&status);
	THROW_ON_FAILURE(status);

	m_shapeCollection = std::make_unique<MeshShapeCollection>(*m_shape, m_blendShapes.get());

	m_renderables = std::make_unique<MeshRenderables>(instanceNumber, *m_shapeCollection, args);

	CONSTRUCTOR_END();
}

Mesh::~Mesh()
{
}

void Mesh::dump(IndentableStream& out, const std::string& name) const
{
	out << quoted(name) << ": {" << endl << indent;

	m_shape->dump(out, "shape");

	if (m_blendShapes)
	{
		out << "," << endl;
		m_blendShapes->dump(out, "blendShapes");
	}

	//m_renderables->dump(cout, "renderables", subIndent);
	//cout << "," << endl;
	
	out << undent << '}' << endl;
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
						cerr << prefix << "ignoring blend controller " << MFnDependencyNode(thisNode).name() << endl;
					}
				}
				else
				{
					cerr << prefix << "node has " << MFnDependencyNode(thisNode).name() << endl;
				}
			}
		}
	}

	return blendController;
}
