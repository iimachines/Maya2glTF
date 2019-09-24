#pragma once

/*

Copyright (C) 2005-2007 Feeling Software Inc.
Portions of the code are:
Copyright (C) 2005-2007 Sony Computer Entertainment America
Copyright (C) 2004-2005 Alias Systems Corp.
Copyright (C) 2017 Wonder Media Group

MIT License: http://www.opensource.org/licenses/mit-license.php
*/

#ifndef __DAG_HELPER_INCLUDED__
#define __DAG_HELPER_INCLUDED__

#include "MayaException.h"
#include "basicTypes.h"

struct DagHelper {
    static MObject getObjectByName(const MString &name);
    static MObject getObjectByName(const std::string &name);

    static MStatus getPlugConnectedTo(const MObject &node,
                                      const MString &attribute, MPlug &plug);

    /** Find a node connected to a node's attribute, returns kNull when not
     * found */
    static MObject findNodeConnectedTo(const MObject &node,
                                       const MString &attribute);

    /* Find the node connected to a plug, returns kNull when not found */
    static MObject findNodeConnectedTo(const MPlug &plug);

    static MObject findSourceNodeConnectedTo(const MObject &node,
                                             const MString &attribute);
    static MObject findSourceNodeConnectedTo(const MPlug &inPlug);

    static MStatus getPlugValue(const MObject &node, const char *attributeName,
                                double &value);
    static MStatus getPlugValue(const MObject &node, const char *attributeName,
                                float &value);
    static MStatus getPlugValue(const MObject &node, const char *attributeName,
                                bool &value);
    static MStatus getPlugValue(const MObject &node, const char *attributeName,
                                int &value);
    static MStatus getPlugValue(const MObject &node, const char *attributeName,
                                MColor &value);
    static MStatus getPlugValue(const MObject &node, const char *attributeName,
                                MString &value);
    static MStatus getPlugValue(const MObject &node, const char *attributeName,
                                MVector &value);
    static MStatus getPlugValue(const MObject &node, const char *attributeName,
                                MStringArray &value);

    static MStatus getPlugValue(const MPlug &plug, bool &value) {
        return plug.getValue(value);
    }
    static MStatus getPlugValue(const MPlug &plug, int &value) {
        return plug.getValue(value);
    }
    static MStatus getPlugValue(const MPlug &plug, short &value) {
        return plug.getValue(value);
    }
    static MStatus getPlugValue(const MPlug &plug, char &value) {
        return plug.getValue(value);
    }
    static MStatus getPlugValue(const MPlug &plug, float &value) {
        return plug.getValue(value);
    }
    static MStatus getPlugValue(const MPlug &plug, double &value) {
        return plug.getValue(value);
    }
    static MStatus getPlugValue(const MPlug &plug, MString &value) {
        return plug.getValue(value);
    }

    static MStatus getPlugValue(const MPlug &plug, MColor &value);
    static MStatus getPlugValue(const MPlug &plug, uint32_t &value);
    static MStatus getPlugValue(const MPlug &plug, uint16_t &value);
    static MStatus getPlugValue(const MPlug &plug, uint8_t &value);
    static MStatus getPlugValue(const MPlug &plug, float &x, float &y);
    static MStatus getPlugValue(const MPlug &plug, float &x, float &y,
                                float &z);
    static MStatus getPlugValue(const MPlug &plug, MVector &value);
    static MStatus getPlugValue(const MPlug &plug, MStringArray &output);

    /** Find a child plug. Returns a null plug when not found. Throws an error
     * on failures */
    static MPlug getChildPlug(const MPlug &parent, const MString &name);

    /** Find a child plug index. Returns -1 when not found or on failure. Useful
     * for performance reasons when iterating over many plugs */
    static int getChildPlugIndex(const MPlug &parent, const MString &name);

    static bool hasConnection(const MPlug &plug, bool asSource = true,
                              bool asDestination = true);

    /*
    static bool			getPlugConnectedTo(const MPlug& inPlug, MPlug&
    plug); static bool			GetPlugArrayConnectedTo(const MObject&
    node, const MString& attribute, MPlug& plug); static int
    GetNextAvailableIndex(const MObject& object, const MString& attribute, int
    startIndex = 0);
    static int			GetNextAvailableIndex(const MPlug& p, int startIndex =
    0); static bool			Connect(const MObject& source, const
    MString& sourceAttribute, const MObject& destination, const MString&
    destinationAttribute); static bool			Connect(const MObject&
    source, const MString& sourceAttribute, const MPlug& destination); static
    bool			Connect(const MPlug& source, const MObject& destination,
    const MString& destinationAttribute); static bool
    Connect(const MPlug& source, const MPlug& destination); static bool
    ConnectToList(const MObject& source, const MString& sourceAttribute, const
    MObject& destination, const MString& destinationAttribute, int* index =
    nullptr);
    static bool			ConnectToList(const MPlug& source, const MObject&
    destination, const MString& destinationAttribute, int* index = nullptr);
    static bool			Disconnect(const MPlug& source, const MPlug&
    destination); static bool			Disconnect(const MPlug& plug,
    bool sources = true, bool destinations = true);

    // Handle mesh-related node connections that use grouped components
    static void			GroupConnect(MPlug& source, const MObject&
    destination, const MObject& finalMesh);

    // Get/set the bind pose for a transform
    //static MMatrix		GetBindPoseInverse(const MObject& controller, const
    MObject& influence);
    //static MStatus		SetBindPoseInverse(const MObject& node, const
    MMatrix& bindPoseInverse);


                                                                                                         // Get/set a plug's value
    static bool			SetPlugValue(MPlug& plug, const MVector& value);
    //static bool			SetPlugValue(MPlug& plug, const MMatrix&
    value); static bool			SetPlugValue(MPlug& plug, const MColor&
    value);
    static bool			SetPlugValue(MPlug& plug, const std::string&
    value); static bool			SetPlugValue(MPlug& plug, const MString&
    value) { return plug.setValue(const_cast<MString&>(value)) ==
    MStatus::kSuccess; } static bool			SetPlugValue(MPlug&
    plug, float value); static bool			SetPlugValue(MPlug&
    plug, double value); static bool			SetPlugValue(MPlug&
    plug, float x, float y);
    static bool			SetPlugValue(MPlug& plug, int value);
    static bool			SetPlugValue(MPlug& plug, bool value);
    static bool			SetPlugValue(MPlug& plug, MStringArray&
    stringArray);

    // Helper to avoid the findPlug.
    template <class ValueType>
    static bool			SetPlugValue(const MObject& node, const char*
    attributeName, const ValueType& value)
    {
        MPlug p = MFnDependencyNode(node).findPlug(attributeName); return
    SetPlugValue(p, value);
    }

    // set an array plug size before creating the element plugs
    static void			SetArrayPlugSize(MPlug& plug, uint size);

    // Attempt to translate a string path/name into a dag path or node
    static MDagPath		GetShortestDagPath(const MObject& node);

    // Create an animation curve for the given plug
    static MObject		CreateAnimationCurve(const MObject& node, const char*
    attributeName, const char* curveType); static MObject
    CreateAnimationCurve(const MPlug& plug, const char* curveType); static bool
    PlugHasAnimation(const MPlug& plug); static MObject
    CreateExpression(const MPlug& plug, const MString& expression);

    // Create a string-typed attribute on a given node
    static MObject		CreateAttribute(const MObject& node, const char*
    attributeName, const char* attributeShortName, MFnData::Type type, const
    char *value);
    static MObject		CreateAttribute(const MObject& node, const char*
    attributeName, const char* attributeShortName, MFnNumericData::Type type,
    const char *value); static MPlug		AddAttribute(const MObject&
    node, const MObject& attribute);

    // get the first empty item in the named array plug
    static unsigned GetFirstEmptyElementId(const MPlug& parent);

    // [PeterV] Get or create a new intermediate shape connected to the
    targetPlug.
    // This is used to make sure we can read valid geometry arriving at the
    targetPlug
    // (e.g. just the input plugs of the blend shape controller and skin
    pre-bind mesh) static MObject GetOrCreateIncomingShapeNode(MPlug&
    targetPlug); static MObject GetOrCreateOutgoingShapeNode(MPlug& sourcePlug);

    enum MessageDirection
    {
        Incoming,
        Outgoing,
    };

    // [PeterV] Create a new message attribute (and plug), if not already
    present.
    // Throws an exception on failure!
    static MPlug AddOrCreateMessagePlug(const MObject& node,
        const char* attributeName, const char* attributeShortName,
        MessageDirection direction, bool& created);
    */

  private:
    template <class ValueType>
    static MStatus getPlugValueImpl(const MObject &node,
                                    const char *attributeName,
                                    ValueType &value) {
        MStatus status;

        MFnDependencyNode dpn(node, &status);
        RETURN_ON_FAILURE(status);

        auto plug = dpn.findPlug(attributeName, &status);
        RETURN_ON_FAILURE(status);

        return getPlugValue(plug, value);
    }
};

#endif
