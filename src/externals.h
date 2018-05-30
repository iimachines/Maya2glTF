#pragma once

#include <csignal>
#include <iostream>
#include <sstream>
#include <cassert>
#include <vector>
#include <algorithm>
#include <array>
#include <memory>
#include <iomanip>
#include <fstream>
#include <filesystem>
#include <cstdarg>
#include <unordered_set>
#include <unordered_map>
#include <bitset>
#include <numeric>
#include <cmath>

#ifdef _MSC_VER
#	pragma  warning(disable:4267)
#endif

#include <GLTFAsset.h>
#include <GLTFScene.h>
#include <GLTFBuffer.h>
#include <GLTFBufferView.h>
#include <GLTFAccessor.h>
#include <GLTFMesh.h>
#include <GLTFPrimitive.h>

#ifdef _MSC_VER
#	pragma  warning(default:4267)
#endif

#include "rapidjson/document.h"
#include "rapidjson/prettywriter.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/writer.h"

#include <gsl/span>

#include <coveo/linq.h>
#include <coveo/enumerable.h>

#include <maya/MPxCommand.h>
#include <maya/MFnPlugin.h>
#include <maya/MIOStream.h>
#include <maya/MGlobal.h>
#include <maya/MArgList.h>
#include <maya/MArgDatabase.h>
#include <maya/MSyntax.h>
#include <maya/MStreamUtils.h>
#include <maya/MFileObject.h>
#include <maya/MFileIO.h>
#include <maya/MSelectionList.h>
#include <maya/MFnMesh.h>
#include <maya/MItMeshPolygon.h>
#include <maya/MFloatPointArray.h>
#include <maya/MFloatVectorArray.h>
#include <maya/MDagPath.h>
#include <maya/MPointArray.h>
#include <maya/MFnAttribute.h>
#include <maya/MFnStringArrayData.h>
#include <maya/MFnMessageAttribute.h>
#include <maya/MFnNumericAttribute.h>
#include <maya/MFnTypedAttribute.h>
#include <maya/MDagPathArray.h>
#include <maya/MFnSet.h>
#include <maya/MFnSingleIndexedComponent.h>
#include <maya/MFnComponentListData.h>
#include <maya/MDagModifier.h>
#include <maya/MMatrix.h>
#include <maya/MFnMatrixData.h>
#include <maya/MFnTransform.h>
#include <maya/MItDependencyGraph.h>
#include <maya/MFnBlendShapeDeformer.h>
#include <maya/MFnPhongShader.h>
#include <maya/MFnLambertShader.h>
#include <maya/MFnBlinnShader.h>
#include <maya/MUuid.h>
#include <maya/MImage.h>
#include <maya/MFloatMatrix.h>
#include <maya/MTime.h>
#include <maya/MAnimControl.h>
#include <maya/M3dView.h>
#include <maya/MFnSkinCluster.h>
#include <maya/MItGeometry.h>
#include <maya/MItDependencyNodes.h>
#include <maya/MItMeshFaceVertex.h>

