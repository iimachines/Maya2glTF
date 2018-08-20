#pragma once
#include "ExportableResources.h"
#include "Transform.h"

class ExportableNode;

typedef std::map<std::string, std::unique_ptr<ExportableNode>> NodeTable;

// Maps each DAG path to the corresponding node
// Owns and creates each node on the fly.
class ExportableScene
{
public:
	explicit ExportableScene(ExportableResources& resources);
	~ExportableScene();

	ExportableResources& resources() const { return m_resources; }

	const Arguments& arguments() const { return m_resources.arguments(); }

	// Update all node transforms using the values at the current frame
	void updateCurrentValues();

	void mergeRedundantShapeNodes();

	GLTF::Scene glScene;

	// Gets or creates the node
	// Returns null if the DAG path has no node
	ExportableNode* getNode(const MDagPath& dagPath);

	// Gets or creates the parent of the node.
	// Returns null if the node has no logical parent.
	ExportableNode* getParent(ExportableNode* node);

	static int distanceToRoot(MDagPath dagPath);

	const NodeTable& table() const { return m_table; }

private:
	DISALLOW_COPY_MOVE_ASSIGN(ExportableScene);

	friend class ExportableNode;

	ExportableResources& m_resources;
	NodeTable m_table;
	NodeTransformCache m_initialTransformCache;
	NodeTransformCache m_currentTransformCache;
};

