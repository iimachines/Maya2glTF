#pragma once

#include "ExportableObject.h"	
#include "ExportableMesh.h"
#include "ExportableScene.h"
#include "Transform.h"


class ExportableNode : public ExportableObject
{
public:
	~ExportableNode();
	
	ExportableMesh* mesh() const { return m_mesh.get(); }

	const MDagPath dagPath;

	bool hasSegmentScaleCompensation;

	double scaleFactor;

	MPoint pivotPoint;
	MMatrix pivotTransform;

	// nullptr for root nodes.
	ExportableNode* parentNode;

	NodeTransformState initialTransformState;
	NodeTransformState currentTransformState;

	std::unique_ptr<NodeAnimation> createAnimation(const ExportableFrames& frameTimes, const double scaleFactor) override;

	// The node that stores the rotation and scale
	// See Transform.h for details
	GLTF::Node& glNodeRS() { return m_glNodes[0]; }
	const GLTF::Node& glNodeRS() const { return const_cast<ExportableNode*>(this)->glNodeRS(); }

	// The node that stores the translation and optional inverse parent scale
	// See Transform.h for details
	GLTF::Node& glNodeTU() { return m_glNodes[hasSegmentScaleCompensation]; }
	const GLTF::Node& glNodeTU() const { return const_cast<ExportableNode*>(this)->glNodeTU(); }

	MDagPath parentDagPath() const { return parentNode ? parentNode->dagPath : MDagPath(); }

	// Update the node transforms using the values at the current frame
	void updateNodeTransforms(NodeTransformCache& transformCache);

private:
	friend class ExportableScene;

	ExportableNode(MDagPath dagPath);

	void load(ExportableScene& scene, NodeTransformCache& transformCache);

	std::array<GLTF::Node, 2> m_glNodes;
	std::unique_ptr<ExportableMesh> m_mesh;

	DISALLOW_COPY_MOVE_ASSIGN(ExportableNode);
};

