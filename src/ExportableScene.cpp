#include "externals.h"
#include "ExportableScene.h"
#include "ExportableNode.h"
#include "MayaException.h"

ExportableScene::ExportableScene(ExportableResources& resources) :m_resources(resources)
{
}

ExportableScene::~ExportableScene() = default;

ExportableNode* ExportableScene::getNode(const MDagPath& dagPath)
{
	MStatus status;

	const std::string fullDagPath{ dagPath.fullPathName(&status).asChar() };
	THROW_ON_FAILURE(status);

	MObject mayaNode = dagPath.node(&status);
	if (mayaNode.isNull() || status.error())
	{
		cerr << "glTF2Maya: skipping '" << fullDagPath << "' as it is not a node" << endl;
		return nullptr;
	}

	auto& ptr = m_table[fullDagPath];
	if (ptr == nullptr)
	{
		ptr.reset(new ExportableNode(dagPath));
		ptr->load(*this);
	}
	return ptr.get();
}

ExportableNode* ExportableScene::getParent(ExportableNode* node)
{
	MStatus status;

	auto parentDagPath = node->dagPath;

	ExportableNode* parentNode = nullptr;

	// Find first selected ancestor node.
	// That is our logical parent.
	while(!parentNode)
	{
		parentDagPath.pop();
		if (parentDagPath.length() <= 0)
			break;

		parentNode = getNode(parentDagPath);
	}

	return parentNode;
}

int ExportableScene::distanceToRoot(MDagPath dagPath)
{
	int distance;

	// Find first selected ancestor node.
	// That is our logical parent.
	for (distance=0; dagPath.length() > 0; ++distance) 
	{
		dagPath.pop();
	}

	return distance;
}
