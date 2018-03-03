#pragma once

class ExportableNode;

typedef std::map<std::string, class ExportableNode*> NodeTable;

// Maps each DAG path to the corresponding node.
class NodeHierarchy
{
public:
	void registerNode(ExportableNode* node);

	ExportableNode* lookupNode(const std::string& fullDagPath) const;

	// Returns null if the node has no logical parent.
	ExportableNode* parentOf(ExportableNode* node) const;

	static int distanceToRoot(ExportableNode* node);

	void computeObjectTransforms();

	const NodeTable& table() const { return m_table; }

private:
	NodeTable m_table;
};

