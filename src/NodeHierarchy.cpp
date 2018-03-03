#include "externals.h"
#include "NodeHierarchy.h"
#include "ExportableNode.h"
#include "MayaException.h"

void NodeHierarchy::registerNode(ExportableNode* node)
{
	m_table[node->dagPath.fullPathName().asChar()] = node;
}

ExportableNode* NodeHierarchy::lookupNode(const std::string& fullDagPath) const
{
	auto it = m_table.find(fullDagPath);
	return it != m_table.end() ? it->second : nullptr;
}

ExportableNode* NodeHierarchy::parentOf(ExportableNode* node) const
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

		const std::string parentFullPath { parentDagPath.fullPathName(&status).asChar() };
		THROW_ON_FAILURE(status);

		parentNode = lookupNode(parentFullPath);
	}

	return parentNode;
}

int NodeHierarchy::distanceToRoot(ExportableNode* node) 
{
	int distance;
	auto dagPath = node->dagPath;

	// Find first selected ancestor node.
	// That is our logical parent.
	for (distance=0; dagPath.length() > 0; ++distance) 
	{
		dagPath.pop();
	}

	return distance;
}

void NodeHierarchy::computeObjectTransforms()
{
	for (auto& it: m_table)
	{
		it.second->connectToHierarchy(*this);
	}
}
