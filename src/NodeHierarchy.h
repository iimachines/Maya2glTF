#pragma once

class ExportableNode;

// Maps each DAG path to the corresponding node.
class NodeHierarchy
{
public:
	void registerNode(ExportableNode* node);

	ExportableNode* lookupNode(const std::string& fullDagPath) const;

	// Returns null if the node has no logical parent.
	ExportableNode* parentOf(ExportableNode* node) const;
	
	void computeObjectTransforms();

private:
	std::map<std::string, class ExportableNode*> m_table;
};

