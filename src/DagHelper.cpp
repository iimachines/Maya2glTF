#include "DagHelper.h"
#include "MayaException.h"
#include "externals.h"

/*
Copyright (C) 2005-2007 Feeling Software Inc.
Portions of the code are:
Copyright (C) 2005-2007 Sony Computer Entertainment America
Copyright (C) 2004-2005 Alias Systems Corp.

MIT License: http://www.opensource.org/licenses/mit-license.php
*/

MObject DagHelper::getObjectByName(const MString &name) {
    MSelectionList selection;
    THROW_ON_FAILURE(selection.add(name));

    MObject o;
    THROW_ON_FAILURE(selection.getDependNode(0, o));
    return o;
}

MObject DagHelper::getObjectByName(const std::string &name) {
    return getObjectByName(MString(name.c_str()));
}

MObject DagHelper::findNodeConnectedTo(const MPlug &plug) {
    MStatus status;
    MPlugArray connections;
    const auto hasConnections =
        plug.connectedTo(connections, true, true, &status);
    THROW_ON_FAILURE(status);

    return hasConnections && connections.length() > 0 ? connections[0].node()
                                                      : MObject::kNullObj;
}

MObject DagHelper::findNodeConnectedTo(const MObject &node,
                                       const MString &attribute) {
    MPlug plug;
    return getPlugConnectedTo(node, attribute, plug) ? plug.node()
                                                     : MObject::kNullObj;
}

MStatus DagHelper::getPlugConnectedTo(const MObject &node,
                                      const MString &attribute,
                                      MPlug &connectedPlug) {
    MStatus status;
    MFnDependencyNode dgFn(node, &status);
    RETURN_ON_FAILURE(status);

    auto plug = dgFn.findPlug(attribute, &status);

    if (status && plug.isConnected()) {
        // Get the connection - there can be at most one input to a plug
        MPlugArray connections;
        plug.connectedTo(connections, true, true, &status);
        RETURN_ON_FAILURE(status);

        assert(connections.length() <= 1);
        if (connections.length() > 0) {
            connectedPlug = connections[0];
            return MStatus::kSuccess;
        }
    }
    return MStatus::kFailure;
}

MObject DagHelper::findSourceNodeConnectedTo(const MObject &node,
                                             const MString &attribute) {
    MStatus status;
    MFnDependencyNode dgFn(node, &status);
    THROW_ON_FAILURE(status);

    auto plug = dgFn.findPlug(attribute, &status);

    if (status && plug.isConnected()) {
        // Get the connection - there can be at most one input to a plug
        MPlugArray connections;
        plug.connectedTo(connections, true, false, &status);
        THROW_ON_FAILURE(status);

        assert(connections.length() <= 1);
        if (connections.length() > 0)
            return connections[0].node();
    }

    return MObject::kNullObj;
}

MObject DagHelper::findSourceNodeConnectedTo(const MPlug &inPlug) {
    MStatus status;
    MPlugArray connections;
    inPlug.connectedTo(connections, true, false, &status);
    THROW_ON_FAILURE(status);

    return connections.length() > 0 ? connections[0].node() : MObject::kNullObj;
}

MStatus DagHelper::getPlugValue(const MPlug &plug, uint32_t &value) {
    int temp;
    const auto status = plug.getValue(temp);
    value = static_cast<uint32_t>(temp);
    return status;
}

MStatus DagHelper::getPlugValue(const MPlug &plug, uint16_t &value) {
    short temp;
    const auto status = plug.getValue(temp);
    value = static_cast<uint16_t>(temp);
    return status;
}

MStatus DagHelper::getPlugValue(const MPlug &plug, uint8_t &value) {
    char temp;
    const auto status = plug.getValue(temp);
    value = static_cast<uint8_t>(temp);
    return status;
}

MStatus DagHelper::getPlugValue(const MObject &node, const char *attributeName,
                                double &value) {
    return getPlugValueImpl(node, attributeName, value);
}

MStatus DagHelper::getPlugValue(const MObject &node, const char *attributeName,
                                float &value) {
    return getPlugValueImpl(node, attributeName, value);
}

MStatus DagHelper::getPlugValue(const MObject &node, const char *attributeName,
                                bool &value) {
    return getPlugValueImpl(node, attributeName, value);
}

MStatus DagHelper::getPlugValue(const MObject &node, const char *attributeName,
                                int &value) {
    return getPlugValueImpl(node, attributeName, value);
}

MStatus DagHelper::getPlugValue(const MObject &node, const char *attributeName,
                                MColor &value) {
    return getPlugValueImpl(node, attributeName, value);
}

MStatus DagHelper::getPlugValue(const MPlug &plug, MColor &value) {
    MStatus status;

    const auto isCompound = plug.isCompound(&status);
    RETURN_ON_FAILURE(status);

    const auto numChildren = plug.numChildren(&status);
    RETURN_ON_FAILURE(status);

    if (isCompound && numChildren >= 3) {
        status = plug.child(0).getValue(value.r);
        RETURN_ON_FAILURE(status);

        status = plug.child(1).getValue(value.g);
        RETURN_ON_FAILURE(status);

        status = plug.child(2).getValue(value.b);
        RETURN_ON_FAILURE(status);

        if (numChildren >= 4) {
            status = plug.child(3).getValue(value.a);
            RETURN_ON_FAILURE(status);
        } else {
            value.a = 1.0f;
        }

        return status;
    }

    return MStatus::kInvalidParameter;
}

MStatus DagHelper::getPlugValue(const MObject &node, const char *attributeName,
                                MString &value) {
    return getPlugValueImpl(node, attributeName, value);
}

MStatus DagHelper::getPlugValue(const MObject &node, const char *attributeName,
                                MStringArray &value) {
    return getPlugValueImpl(node, attributeName, value);
}

MStatus DagHelper::getPlugValue(const MPlug &plug, MStringArray &output) {
    MStatus status;

    MObject str_obj;
    status = plug.getValue(str_obj);
    RETURN_ON_FAILURE(status);

    MFnStringArrayData f_astr(str_obj, &status);
    RETURN_ON_FAILURE(status);

    const auto len = f_astr.length(&status);
    RETURN_ON_FAILURE(status);

    for (unsigned int i = 0; i < len; ++i) {
        const MString &val = f_astr[i];
        status = output.append(val);
        RETURN_ON_FAILURE(status);
    }

    return MStatus::kSuccess;
}

MStatus DagHelper::getPlugValue(const MPlug &plug, float &x, float &y) {
    MObject obj;
    MStatus status = plug.getValue(obj);
    RETURN_ON_FAILURE(status);

    MFnNumericData fcolor(obj, &status);
    RETURN_ON_FAILURE(status);

    return fcolor.getData(x, y);
}

MStatus DagHelper::getPlugValue(const MPlug &plug, float &x, float &y,
                                float &z) {
    MObject obj;
    MStatus status = plug.getValue(obj);
    RETURN_ON_FAILURE(status);

    MFnNumericData fcolor(obj, &status);
    RETURN_ON_FAILURE(status);

    return fcolor.getData(x, y, z);
}

MStatus DagHelper::getPlugValue(const MObject &node, const char *attributeName,
                                MVector &value) {
    return getPlugValueImpl(node, attributeName, value);
}

MStatus DagHelper::getPlugValue(const MPlug &plug, MVector &value) {
    MObject obj;
    auto status = plug.getValue(obj);
    RETURN_ON_FAILURE(status);

    status = plug.getValue(obj);
    RETURN_ON_FAILURE(status);

    MFnNumericData data(obj);

    double x, y, z;
    status = data.getData(x, y, z);
    RETURN_ON_FAILURE(status);

    value = MVector(x, y, z);
    return MStatus::kSuccess;
}

MPlug DagHelper::getChildPlug(const MPlug &parent, const MString &name) {
    MStatus status;

    const auto childCount = parent.numChildren(&status);
    THROW_ON_FAILURE(status);

    // Check shortNames first
    for (unsigned i = 0; i < childCount; ++i) {
        auto child = parent.child(i, &status);
        THROW_ON_FAILURE(status);

        MFnAttribute attributeFn(child.attribute(&status));
        THROW_ON_FAILURE(status);

        const auto n = attributeFn.shortName(&status);
        THROW_ON_FAILURE(status);

        if (n == name)
            return child;
    }

    // Check longNames second, use shortNames!
    for (unsigned i = 0; i < childCount; ++i) {
        auto child = parent.child(i, &status);
        THROW_ON_FAILURE(status);

        MFnAttribute attributeFn(child.attribute(&status));
        THROW_ON_FAILURE(status);

        const auto n = attributeFn.name(&status);
        THROW_ON_FAILURE(status);

        if (n == name)
            return child;
    }

    return MPlug();
}

int DagHelper::getChildPlugIndex(const MPlug &parent, const MString &name) {
    MStatus status;
    const auto childCount = parent.numChildren(&status);
    CHECK_MSTATUS_AND_RETURN(status, -1);

    // Check shortNames first
    for (unsigned i = 0; i < childCount; ++i) {
        auto child = parent.child(i, &status);
        CHECK_MSTATUS_AND_RETURN(status, -1);

        MFnAttribute attributeFn(child.attribute());
        const auto n = attributeFn.shortName();
        if (n == name)
            return i;
    }

    // Check longNames second, use shortNames!
    for (unsigned i = 0; i < childCount; ++i) {
        auto child = parent.child(i, &status);
        CHECK_MSTATUS_AND_RETURN(status, -1);

        MFnAttribute attributeFn(child.attribute());
        const auto n = attributeFn.name();
        if (n == name)
            return i;
    }

    return -1;
}

bool DagHelper::hasConnection(const MPlug &plug, const bool asSource,
                              const bool asDestination) {
    MStatus status;

    MPlugArray plugs;
    plug.connectedTo(plugs, asDestination, asSource, &status);
    THROW_ON_FAILURE(status);

    if (plugs.length() > 0)
        return true;

    return plug.numConnectedChildren() > 0;
}

#if 0
bool DagHelper::getPlugConnectedTo(const MPlug& inPlug, MPlug& plug)
{
	MStatus status;

	MPlugArray connections;
	inPlug.connectedTo(connections, true, true);
	if (connections.length() > 0)
	{
		plug = connections[0];
		return true;
	}

	return false;
}

//
// Find a node connected to a node's array attribute
//
bool DagHelper::GetPlugArrayConnectedTo(const MObject& node, const MString& attribute, MPlug& connectedPlug)
{
	MStatus status;
	MFnDependencyNode dgFn(node);
	MPlug plug = dgFn.findPlug(attribute, &status);
	if (status != MS::kSuccess)
	{
		MGlobal::displayWarning(MString("couldn't find plug on attribute ") +
			attribute + MString(" on object ") + dgFn.name());
		return false;
	}

	if (plug.numElements() < 1)
	{
		MGlobal::displayWarning(MString("plug array doesn't have any connection on attribute ") +
			attribute + MString(" on object ") + dgFn.name());
		return false;
	}

	MPlug firstElementPlug = plug.connectionByPhysicalIndex(0);

	// Get the connection - there can be at most one input to a plug
	//
	MPlugArray connections;
	firstElementPlug.connectedTo(connections, true, true);
	if (connections.length() == 0)
	{
		MGlobal::displayWarning(MString("plug connected to an empty array on attribute ") +
			attribute + MString(" on object ") + dgFn.name());
		return false;
	}

	connectedPlug = connections[0];
	return true;
}

bool DagHelper::Connect(const MObject& source, const MString& sourceAttribute, const MObject& destination, const MString& destinationAttribute)
{
	MStatus status;
	MFnDependencyNode srcFn(source);
	MFnDependencyNode destFn(destination);

	MPlug src = srcFn.findPlug(sourceAttribute, &status);
	if (status != MStatus::kSuccess) return false;

	MPlug dest = destFn.findPlug(destinationAttribute, &status);
	if (status != MStatus::kSuccess) return false;

	MDGModifier modifier;
	modifier.connect(src, dest);
	status = modifier.doIt();

	return status == MStatus::kSuccess;
}

bool DagHelper::Connect(const MObject& source, const MString& sourceAttribute, const MPlug& destination)
{
	MStatus status;
	MFnDependencyNode srcFn(source);

	MPlug src = srcFn.findPlug(sourceAttribute, &status);
	if (status != MStatus::kSuccess) return false;

	MDGModifier modifier;
	modifier.connect(src, destination);
	status = modifier.doIt();

	return status == MStatus::kSuccess;
}

bool DagHelper::Connect(const MPlug& source, const MObject& destination, const MString& destinationAttribute)
{
	MStatus status;
	MFnDependencyNode destFn(destination);

	MPlug dst = destFn.findPlug(destinationAttribute, &status);
	if (status != MStatus::kSuccess) return false;

	MDGModifier modifier;
	status = modifier.connect(source, dst);
	if (status != MStatus::kSuccess) return false;
	status = modifier.doIt();

	return status == MStatus::kSuccess;
}

bool DagHelper::Connect(const MPlug& source, const MPlug& destination)
{
	MDGModifier modifier;
	modifier.connect(source, destination);
	MStatus status = modifier.doIt();

	return status == MStatus::kSuccess;
}

bool DagHelper::ConnectToList(const MObject& source, const MString& sourceAttribute, const MObject& destination, const MString& destinationAttribute, int* index)
{
	MStatus status;
	MFnDependencyNode srcFn(source);

	MPlug src = srcFn.findPlug(sourceAttribute, &status);
	if (status != MStatus::kSuccess) return false;

	return ConnectToList(src, destination, destinationAttribute, index);
}

bool DagHelper::ConnectToList(const MPlug& source, const MObject& destination, const MString& destinationAttribute, int* _index)
{
	MStatus status;
	MFnDependencyNode destFn(destination);
	MPlug dest = destFn.findPlug(destinationAttribute, &status);
	if (status != MStatus::kSuccess) return false;
	if (!dest.isArray()) return false;

	int index = (_index != nullptr) ? *_index : -1;
	if (index < 0)
	{
		index = GetNextAvailableIndex(dest, (int)dest.evaluateNumElements());
		if (_index != nullptr) *_index = index;
	}

	MPlug d = dest.elementByLogicalIndex(index);
	MDGModifier modifier;
	modifier.connect(source, d);
	status = modifier.doIt();
	return status == MStatus::kSuccess;
}

int DagHelper::GetNextAvailableIndex(const MObject& object, const MString& attribute, int startIndex)
{
	MPlug p = MFnDependencyNode(object).findPlug(attribute);
	if (p.node().isNull()) return -1;
	return GetNextAvailableIndex(p, startIndex);
}

int DagHelper::GetNextAvailableIndex(const MPlug& p, int startIndex)
{
	if (startIndex < 0) startIndex = 0;

	// Look for the next available plug
	for (uint i = (uint)startIndex; i < (uint)startIndex + 100; ++i)
	{
		MPlug possibleDestination = p.elementByLogicalIndex(i);
		if (!DagHelper::HasConnection(possibleDestination))
		{
			return i;
		}
	}
	return -1;
}

/*
// Retrieve the bind pose for a controller/joint pair
//
MMatrix DagHelper::GetBindPoseInverse(const MObject& controller, const MObject& influence)
{
MStatus status;
if (controller.apiType() == MFn::kSkinClusterFilter)
{
MFnSkinCluster controllerFn(controller);

// Find the correct index for the pre-bind matrix
uint index = controllerFn.indexForInfluenceObject(MDagPath::getAPathTo(influence), &status);
if (status != MStatus::kSuccess) return MMatrix::identity;

MPlug preBindMatrixPlug = controllerFn.findPlug("bindPreMatrix", &status);
preBindMatrixPlug = preBindMatrixPlug.elementByLogicalIndex(index, &status);
if (status != MStatus::kSuccess) return MMatrix::identity;

// Get the plug's matrix
MMatrix ret;
if (!DagHelper::getPlugValue(preBindMatrixPlug, ret)) return MMatrix::identity;
return ret;
}
else if (controller.apiType() == MFn::kJointCluster)
{
MMatrix ret;
DagHelper::getPlugValue(influence, "bindPose", ret);
return ret.inverse();
}
else return MMatrix::identity;
}

// set the bind pose for a transform
//
MStatus DagHelper::SetBindPoseInverse(const MObject& node, const MMatrix& bindPoseInverse)
{
MStatus status;
MFnDependencyNode dgFn(node);
MPlug bindPosePlug = dgFn.findPlug("bindPose", &status);
if (status != MS::kSuccess)
{
MGlobal::displayWarning(MString("No bindPose found on node ") + dgFn.name());
return status;
}

MFnMatrixData matrixFn;
MObject val = matrixFn.create(bindPoseInverse.inverse(), &status);
MObject invval = matrixFn.create(bindPoseInverse, &status);
if (status != MS::kSuccess)
{
MGlobal::displayWarning(MString("Error setting bindPose on node ") + dgFn.name());
return status;
}

// set the bind pose on the joint itself
//
bindPosePlug.setValue(val);

// Now, perhaps more significantly, see if there's a
// skinCluster using this bone and update its bind
// pose (as the joint bind pose is not connected to
// the skin - it's set at bind time from the joint's
// current position, and our importer may not want to
// disturb the current scene state just to put bones
// in a bind position before creating skin clusters)
//
MObject _node(node);
MItDependencyGraph it(_node, MFn::kSkinClusterFilter);
while (!it.isDone())
{
MPlug plug = it.thisPlug();
unsigned int idx = plug.logicalIndex();
MFnDependencyNode skinFn(plug.node());
MPlug skinBindPosePlug = skinFn.findPlug("bindPreMatrix", &status);
if (status == MS::kSuccess)
{
// The skinCluster stores inverse inclusive matrix
// so notice we use invval (the MObject created off
// the inverse matrix here)
//
skinBindPosePlug = skinBindPosePlug.elementByLogicalIndex(idx);
skinBindPosePlug.setValue(invval);
}
it.next();
}

return status;
}
*/

bool DagHelper::SetPlugValue(MPlug& plug, const MVector& value)
{
	MStatus status;
	MFnNumericData dataCreator;

	MObject float3Data = dataCreator.create(MFnNumericData::k3Float, &status);
	if (status != MStatus::kSuccess) return false;
	dataCreator.setData((float)value.x, (float)value.y, (float)value.z);

	status = plug.setValue(float3Data);
	if (status != MStatus::kSuccess) return false;

	return true;
}

bool DagHelper::SetPlugValue(MPlug& plug, const MColor& value)
{
	MStatus status;
	if (plug.isCompound() && plug.numChildren() >= 3)
	{
		MPlug rPlug = plug.child(0, &status);
		if (status != MStatus::kSuccess) return false;
		status = rPlug.setValue(value.r);
		if (status != MStatus::kSuccess) return false;

		MPlug gPlug = plug.child(1, &status);
		if (status != MStatus::kSuccess) return false;
		status = gPlug.setValue(value.g);
		if (status != MStatus::kSuccess) return false;

		MPlug bPlug = plug.child(2, &status);
		if (status != MStatus::kSuccess) return false;
		status = bPlug.setValue(value.b);
		if (status != MStatus::kSuccess) return false;

		if (plug.numChildren() >= 4)
		{
			MPlug aPlug = plug.child(3, &status);
			if (status != MStatus::kSuccess) return false;
			status = aPlug.setValue(value.a);
			if (status != MStatus::kSuccess) return false;
		}
	}

	return true;
}

/*
bool DagHelper::SetPlugValue(MPlug& plug, const MMatrix& value)
{
MStatus status;
MFnMatrixData dataCreator;

MObject matrixData = dataCreator.create(value, &status);
if (status != MStatus::kSuccess) return false;

status = plug.setValue(matrixData);
if (status != MStatus::kSuccess) return false;

return true;
}
*/

bool DagHelper::SetPlugValue(MPlug& plug, const std::string& value)
{
	MStatus status;
	status = plug.setValue(value.c_str());
	return status == MStatus::kSuccess;
}

bool DagHelper::SetPlugValue(MPlug& plug, float value)
{
	MStatus status;
	status = plug.setValue(value);
	return status == MStatus::kSuccess;
}

bool DagHelper::SetPlugValue(MPlug& plug, double value)
{
	MStatus status;
	status = plug.setValue(value);
	return status == MStatus::kSuccess;
}

bool DagHelper::SetPlugValue(MPlug& plug, float x, float y)
{
	MFnNumericData data;
	MObject obj = data.create(MFnNumericData::k2Float);
	data.setData(x, y);
	return plug.setValue(obj);
}

bool DagHelper::SetPlugValue(MPlug& plug, int value)
{
	MStatus status;
	status = plug.setValue(value);
	return status == MStatus::kSuccess;
}

bool DagHelper::SetPlugValue(MPlug& plug, bool value)
{
	MStatus status;
	status = plug.setValue(value);
	return status == MStatus::kSuccess;
}

bool DagHelper::SetPlugValue(MPlug& plug, MStringArray& stringArray)
{
	MObject obj;
	MFnStringArrayData fstr;
	obj = fstr.create(stringArray);
	return plug.setValue(obj);
}

void DagHelper::SetArrayPlugSize(MPlug& plug, uint size)
{
	if (plug.node().isNull()) return;

#if MAYA_API_VERSION >= 800
	CHECK_MSTATUS(plug.setNumElements(size));
#else
	MObject node = plug.node();
	MString plugPath = plug.info();
	if (node.hasFn(MFn::kDagNode))
	{
		MFnDagNode dagFn(node);
		int dot = plugPath.index('.');
		plugPath = dagFn.fullPathName() + plugPath.substring(dot, plugPath.length());
	}
	MString command = MString("setAttr -s ") + size + " \"" + plugPath + "\";";
	MGlobal::executeCommand(command);
#endif // MAYA 8.00+
}

// Creates a typed attribute. Used for maya "notes" attributes.
MObject DagHelper::CreateAttribute(const MObject& node, const char* attributeName, const char* attributeShortName, MFnNumericData::Type type, const char *value)
{
	// Before creating a new attribute: verify that an old one doesn't already exist
	MStatus status;
	MObject attribute;
	MFnDependencyNode nodeFn(node);
	MPlug plug = nodeFn.findPlug(attributeShortName, status);
	if (status != MStatus::kSuccess)
	{
		MFnNumericAttribute attr;
		MStatus status;
		attribute = attr.create(attributeName, attributeShortName, type, 0, &status);
		if (status != MStatus::kSuccess) return MObject::kNullObj;
		attr.setStorable(true);
		attr.setKeyable(false);
		attr.setCached(true);
		attr.setReadable(true);
		attr.setWritable(true);

		status = nodeFn.addAttribute(attribute, MFnDependencyNode::kLocalDynamicAttr);
		if (status != MStatus::kSuccess) return MObject::kNullObj;
		plug = nodeFn.findPlug(attribute, &status);
		if (status != MStatus::kSuccess) return MObject::kNullObj;
	}
	else
	{
		attribute = plug.attribute(&status);
	}

	status = plug.setValue(value);
	if (status != MStatus::kSuccess) return MObject::kNullObj;
	return attribute;
}

MObject DagHelper::CreateAttribute(const MObject& node, const char* attributeName, const char* attributeShortName, MFnData::Type type, const char *value)
{
	// Before creating a new attribute: verify that an old one doesn't already exist
	MStatus status;
	MObject attribute;
	MFnDependencyNode nodeFn(node);
	MPlug plug = nodeFn.findPlug(attributeShortName, status);
	if (status != MStatus::kSuccess)
	{
		MFnTypedAttribute attr;
		MStatus status;
		attribute = attr.create(attributeName, attributeShortName, type, &status);
		if (status != MStatus::kSuccess) return MObject::kNullObj;
		attr.setStorable(true);
		attr.setKeyable(false);
		attr.setCached(true);
		attr.setReadable(true);
		attr.setWritable(true);

		status = nodeFn.addAttribute(attribute, MFnDependencyNode::kLocalDynamicAttr);
		if (status != MStatus::kSuccess) return MObject::kNullObj;
		plug = nodeFn.findPlug(attribute, &status);
		if (status != MStatus::kSuccess) return MObject::kNullObj;
	}
	else
	{
		attribute = plug.attribute(&status);
	}

	status = plug.setValue(value);
	if (status != MStatus::kSuccess) return MObject::kNullObj;
	return attribute;
}

MPlug DagHelper::AddAttribute(const MObject& node, const MObject& attribute)
{
	MPlug plug;
	MFnAttribute attributeFn(attribute);
	MFnDependencyNode depFn(node);
	MStatus status = depFn.addAttribute(attribute, MFnDependencyNode::kLocalDynamicAttr);
	if (status == MStatus::kSuccess)
	{
		plug = depFn.findPlug(attribute);
	}
	return plug;
}

// Get a dag path or node from a string
MDagPath DagHelper::GetShortestDagPath(const MObject& node)
{
	MDagPathArray paths;
	MDagPath::getAllPathsTo(node, paths);
	MDagPath shortestPath;
	if (paths.length() > 0)
	{
		shortestPath = paths[0];
		for (uint i = 1; i < paths.length(); ++i)
		{
			if (shortestPath.length() > paths[i].length())
			{
				shortestPath = paths[i];
			}
		}
	}
	return shortestPath;
}

void DagHelper::GroupConnect(MPlug& source, const MObject& destination, const MObject& finalMesh)
{
	MFnDependencyNode destinationFn(destination);
	MFnDagNode finalMeshFn(finalMesh);

	// Create the set which will hold the connected components
	MFnSet objectSetFn;
	MSelectionList clusterComponentList;
	MObject objectSet = objectSetFn.create(clusterComponentList, MFnSet::kVerticesOnly, false);
	objectSetFn.setName(destinationFn.name() + "set");

	// Connect the set to the destination and the finalMesh
	DagHelper::ConnectToList(destination, "message", objectSet, "usedBy");

	// Create the groupId node
	MFnDependencyNode groupId;
	groupId.create("groupId");
	DagHelper::SetPlugValue(groupId.object(), "isHistoricallyInteresting", 0);

	// Create the groupParts node
	MFnDependencyNode groupParts;
	groupParts.create("groupParts");
	DagHelper::SetPlugValue(groupParts.object(), "isHistoricallyInteresting", 0);

	// Tell the groupParts to connect all the vertices of the mesh
	MFnSingleIndexedComponent allVerticesComponent;
	MObject allVerticesObject = allVerticesComponent.create(MFn::kMeshVertComponent);
	allVerticesComponent.setComplete(true);
	MFnComponentListData componentListData;
	MObject componentList = componentListData.create();
	componentListData.add(allVerticesObject);
	MPlug inputComponentsPartsPlug = groupParts.findPlug("inputComponents");
	inputComponentsPartsPlug.setValue(componentList);

	// Tell the ouput node to expect the groupId
	MPlug instanceObjectGroupsPlug = finalMeshFn.findPlug("instObjGroups");
	instanceObjectGroupsPlug = instanceObjectGroupsPlug.elementByLogicalIndex(0);
	MPlug objectGroupsPlug = DagHelper::getChildPlug(instanceObjectGroupsPlug, "og"); // "objectGroups"
	MPlug objectGroupPlug = objectGroupsPlug.elementByLogicalIndex(objectGroupsPlug.numElements());
	MPlug groupIdPlug = DagHelper::getChildPlug(objectGroupPlug, "gid"); // "objectGroupId"
	DagHelper::Connect(groupId.object(), "id", groupIdPlug);

	// Tell the groupId about the set to implied in the connection
	DagHelper::ConnectToList(groupId.object(), "msg", objectSetFn.object(), "gn");

	// Connect up the set and the groupId implication within the final mesh
	MPlug groupColorPlug = DagHelper::getChildPlug(objectGroupPlug, "gco"); // "objectGrpColor"
	DagHelper::Connect(objectSet, "memberWireframeColor", groupColorPlug);
	DagHelper::ConnectToList(objectGroupPlug, objectSet, "dagSetMembers");

	// Connect the output with the groupParts
	MPlug inputGlobalPlug = destinationFn.findPlug("input");
	inputGlobalPlug = inputGlobalPlug.elementByLogicalIndex(inputGlobalPlug.numElements());
	MPlug inputGeometryPlug = DagHelper::getChildPlug(inputGlobalPlug, "ig"); // "inputGeometry"
	DagHelper::Connect(groupParts.object(), "og", inputGeometryPlug);

	// Connect the output with the groupId
	groupIdPlug = DagHelper::getChildPlug(inputGlobalPlug, "gi"); // "groupId"
	DagHelper::Connect(groupId.object(), "id", groupIdPlug);

	// Connect the input with the groupParts
	MObject sourceNode = source.node();
	MString sourceName;
	if (!sourceNode.hasFn(MFn::kDagNode)) sourceName = source.info();
	else
	{
		MFnDagNode sourceNodeFn(source.node());
		MFnDagNode parentNodeFn(sourceNodeFn.parent(0));
		sourceName = parentNodeFn.fullPathName() + "|" + source.info();
	}
	MGlobal::executeCommand(MString("connectAttr ") + sourceName + " " + groupParts.name() + ".inputGeometry;");

	// Connect the groupId and the groupParts together
	DagHelper::Connect(groupId.object(), "id", groupParts.object(), "groupId");
}

bool DagHelper::Disconnect(const MPlug& source, const MPlug& destination)
{
	MDGModifier mod;
	mod.disconnect(source, destination);
	MStatus s = mod.doIt();
	return !s.error();
}

bool DagHelper::Disconnect(const MPlug& plug, bool sources, bool destinations)
{
	MDGModifier mod;
	MPlugArray connectedPlugs;
	if (sources)
	{
		if (plug.connectedTo(connectedPlugs, sources, false))
		{
			for (uint i = 0; i < connectedPlugs.length(); ++i)
			{
				MPlug p = connectedPlugs[i];
				mod.disconnect(p, plug);
			}
		}
	}
	if (destinations)
	{
		if (plug.connectedTo(connectedPlugs, false, destinations))
		{
			for (uint i = 0; i < connectedPlugs.length(); ++i)
			{
				MPlug p = connectedPlugs[i];
				mod.disconnect(plug, p);
			}
		}
	}
	return mod.doIt() == MStatus::kSuccess;
}

// Create an animation curve for the given plug
MObject DagHelper::CreateAnimationCurve(const MObject& node, const char* attributeName, const char* curveType)
{
	MFnDependencyNode fn(node); return CreateAnimationCurve(fn.findPlug(attributeName), curveType);
}
MObject DagHelper::CreateAnimationCurve(const MPlug& plug, const char* curveType)
{
	MStatus status;
	MFnDependencyNode curveFn;
	curveFn.create(curveType, &status);
	if (status == MStatus::kSuccess)
	{
		DagHelper::Connect(curveFn.object(), "output", plug);
	}
	return curveFn.object();
}

MObject DagHelper::CreateExpression(const MPlug& plug, const MString& expression)
{
	MFnDependencyNode expressionFn;
	MObject expressionObj = expressionFn.create("expression");
	DagHelper::SetPlugValue(expressionObj, "expression", expression);

	MPlug output = expressionFn.findPlug("output");
	MPlug firstOutput = output.elementByLogicalIndex(0);
	DagHelper::Connect(firstOutput, plug);
	return expressionObj;
}

bool DagHelper::PlugHasAnimation(const MPlug& plug)
{
	MPlugArray connections;
	plug.connectedTo(connections, true, false);
	unsigned int connectionsCount = connections.length();
	for (unsigned int i = 0; i < connectionsCount; i++)
	{
		MPlug connectedToPlug = connections[i];
		MObject nodeObj = connectedToPlug.node();
		MFnDependencyNode nodeFn(nodeObj);
		MString typeName = nodeFn.typeName();
		if ((typeName == "animCurveTU") || (typeName == "animCurveTL")
			|| (typeName == "animCurveTA"))
		{
			return true;
		}
	}
	return false;
}

// get the first empty item in the named array plug
unsigned DagHelper::GetFirstEmptyElementId(const MPlug& parent)
{
	unsigned num_element = 1;
	if (parent.numElements() > num_element) num_element = parent.numElements();
	for (unsigned i = 0; i < num_element; i++)
	{
		if (!parent.elementByLogicalIndex(i).isConnected()) return i;
	}
	return parent.numElements() + 1;
}


MPlug DagHelper::AddOrCreateMessagePlug(const MObject& node,
	const char* attributeName, const char* attributeShortName,
	MessageDirection direction, bool& created)
{
	// Before creating a new attribute: verify that an old one doesn't already exist
	created = false;
	MStatus status;
	MFnDependencyNode nodeFn(node);
	MPlug plug = nodeFn.findPlug(attributeShortName, &status);
	if (status != MStatus::kSuccess)
	{
		MFnMessageAttribute fnMessageAttribute;
		MObject attribute = fnMessageAttribute.create(attributeName, attributeShortName, &status);
		THROW_ON_FAILURE(status);

		THROW_ON_FAILURE(fnMessageAttribute.setStorable(true));
		THROW_ON_FAILURE(fnMessageAttribute.setKeyable(false));
		THROW_ON_FAILURE(fnMessageAttribute.setCached(true));
		THROW_ON_FAILURE(fnMessageAttribute.setReadable(direction == Outgoing));
		THROW_ON_FAILURE(fnMessageAttribute.setWritable(direction == Incoming));

		status = nodeFn.addAttribute(attribute, MFnDependencyNode::kLocalDynamicAttr);
		THROW_ON_FAILURE(status);

		plug = nodeFn.findPlug(attribute, &status);
		THROW_ON_FAILURE(status);

		created = true;
	}


	return plug;
}
#endif
