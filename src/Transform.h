#pragma once

bool hasOrthogonalAxes(const MMatrix& m);

class ExportableNode;

/*
* NOTE: 
* in the code below we use OpenGL matrix math (mul from right to left), so to transform a point P by matrices M1 then M2 we write M2 * M1 * P
* Maya used DirectX matrix math (mul from left to right), so it transforms the point by P * M1 * M2
* 
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
* [Tk * Sk] * [Ri * Si] = [Tm * Um] * [Rm * Sm]
* 
* 
* Furthermore, Maya transform nodes can have pivot points.
* 
* In general, a pivot point transform is represented as Pm * Tm * Rm * Sm * inverse(Pm),
* where Pm is the pivot translation and inverse(Pm) is the negative translation
* 
* We can combine Pm and Tm into a new translation Tm', but we're stuck with inverse(Pm)
* 
* To simulate this in GLTF, we need an extra node #k
*
* [Tk * Sk * Rk] * [Ti] = [(Pm * Tm) * Rm * Sm] * [inverse(Pm)]
*
*/

typedef std::array<GLTF::Node::TransformTRS, 2> NodeTransformArray;

class NodeTransformState
{
public:

	// Can the local matrix be represented by the one or two local transforms?
	// False if the local Maya matrix is skewed, even after dealing with segment scale compensation.
	bool hasValidLocalTransforms = false;

	// Is an extra GLTF node is required to represent the Maya transform?
	// This occurs for Maya joints with segment scale compensation (SSC) and transforms with non-zero pivot points.
	bool requiresExtraNode = false;

	// Without segment scale compensation (SSC), 
	// only the first item is needed, 
	// the second will be the identity.
	NodeTransformArray localTransforms;

	// For Maya joints with SSC, the GLTF transform storing the rotation and scale
	// For Maya transforms with pivot points, the GLTF transform storing the negative pivot offset
	// Otherwise the GLTF transform storing the rotation, scale and translation
	const GLTF::Node::TransformTRS& primaryTRS() const { return localTransforms[0]; }

	// For Maya joints with SSC, the GLTF transform storing the translation and inverse parent scale
	// For Maya transforms with pivot points, the GLTF transform storing the rotation, scale and (translation+pivot offset) combined
	// Otherwise this is an identity transform
	const GLTF::Node::TransformTRS& secondaryTRS() const { return localTransforms[requiresExtraNode]; }

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
