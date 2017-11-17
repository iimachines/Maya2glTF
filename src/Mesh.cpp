#include "externals.h"
#include "Mesh.h"
#include "MayaException.h"

Mesh::Mesh(const MDagPath& dagPath) 
{
	MStatus status;

	const MFnMesh fnMesh(dagPath, &status);
	THROW_ON_FAILURE(status);

	m_shape = std::make_unique<MeshShape>(fnMesh);

	auto instanceNumber = dagPath.instanceNumber(&status);
	THROW_ON_FAILURE(status);

	// Find blend shapes. The weights of shapes are added as extra semantics
	MObject blendShapeController = tryExtractBlendController(fnMesh);
	if (!blendShapeController.isNull())
	{
		m_blendShapes = std::make_unique<MeshBlendShapes>(blendShapeController);
	}

	auto& shadingPerInstance = m_shape->indices().shadingPerInstance();

	auto& shading = shadingPerInstance.at(instanceNumber);
	const auto shaderCount = shading.shaderCount();
	for (auto shaderIndex = 0; shaderIndex < shaderCount; ++shaderIndex)
	{
		// If the shader is not used by any primitive, skip it
		if (shading.isShaderUsed[shaderIndex])
		{
			auto renderable = std::make_unique<MeshRenderable>(instanceNumber, shaderIndex, *m_shape);
			if (renderable->indices().size())
			{
				m_renderables.emplace_back(std::move(renderable));
			}
		}
	}
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

	m_blendShapes->dump("blendShapes", subIndent);
	cout << "," << endl;

	cout << subIndent << std::quoted("renderables") << ": [" << endl;
	const auto subIndent2 = subIndent + "\t";
	for (auto && renderable: m_renderables)
	{
		renderable->dump(subIndent2);
		cout << "," << endl;
	}
	cout << subIndent << "]" << endl;
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
