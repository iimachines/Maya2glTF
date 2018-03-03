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

	auto& dagPath = node->dagPath;

	MFnDagNode fnDagNode(dagPath, &status);
	THROW_ON_FAILURE(status);

	int pathLength = dagPath.pathCount(&status);
	THROW_ON_FAILURE(status);

	// Find first selected ancestor node.
	// That is our logical parent.
	while (--pathLength > 0)
	{
		MDagPath parentDagPath;
		status = dagPath.getPath(parentDagPath, pathLength);

		const auto parentNode = lookupNode(parentDagPath.fullPathName(&status).asChar());
		THROW_ON_FAILURE(status);

		if (parentNode)
			return parentNode;
	}

	return nullptr;
}

void NodeHierarchy::computeObjectTransforms()
{
	for (auto& it: m_table)
	{
		it.second->connectToHierarchy(*this);
	}
}
