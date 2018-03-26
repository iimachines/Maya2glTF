#pragma once

class ExportableNode;

/*
* The local transform of a GLTF node #i is represented as Ti * Ri * Si
*
* In Maya, joints can ignore the scaling of the parent (when the Segment Scale Compensate flag is set)
* The local transform of such Maya joints is Tm * Um * Rm * Sm
* where Ui undoes the scaling of the parent (the inverse parent scale)
* See http://download.autodesk.com/us/maya/2010help/API/class_m_fn_ik_joint.html
*
* To simulate this in GLTF, we need an extra node #k
*
* The combined transform of both GLTF nodes will be
*
* Tk * Sk * Ri * Si = Tm * Um * Rm * Sm
* 
*/

typedef std::array<GLTF::Node::TransformTRS, 2> NodeTransformArray;

class NodeTransformState
{
public:

	// Can the local matrix be represented by the one or two local transforms?
	// False if the local Maya matrix is skewed, even after dealing with segment scale compensation.
	bool hasValidLocalTransforms = false;
	
	bool hasSegmentScaleCompensation = false;

	// Without segment scale compensation, 
	// only the first item is needed, 
	// the second will be the identity.
	NodeTransformArray localTransforms;

	// The transform storing the rotation and scale
	const GLTF::Node::TransformTRS& localTransformRS() const { return localTransforms[0]; }

	// The transform storing the translation and inverse parent scale
	const GLTF::Node::TransformTRS& localTransformTU() const { return localTransforms[hasSegmentScaleCompensation]; }

	DEFAULT_COPY_MOVE_ASSIGN_CTOR_DTOR(NodeTransformState);

private:
	friend class NodeTransformCache;

	int isInitialized = 0;
};

class NodeTransformCache
{
public:
	NodeTransformCache() = default;
	~NodeTransformCache() = default;

	const NodeTransformState& getTransform(const ExportableNode* node, double scaleFactor);

private:
	DISALLOW_COPY_MOVE_ASSIGN(NodeTransformCache);

	std::unordered_map<const ExportableNode*, NodeTransformState> m_table;
};

/*
namespace Transform
{
	bool hasOrthogonalAxes(const MMatrix& m, const double epsilon = 1e-3f);

	GLTF::Node::TransformMatrix toGLTF(const MMatrix& matrix);

	MMatrix getObjectSpaceMatrix(MDagPath childPath, MDagPath parentPath);

	GLTF::Node::TransformTRS toTRS(const MMatrix& localMatrix, const double scaleFactor, const double precision = 1e9);
	GLTF::Node::TransformTRS toTRS(const MMatrix& matrix, const double scaleFactor, const char* context, const double precision = 1e9);
}
*/