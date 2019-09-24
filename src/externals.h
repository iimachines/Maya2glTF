#pragma once

#include <algorithm>
#include <array>
#include <bitset>
#include <cassert>
#include <cctype>
#include <cerrno>
#include <chrono>
#include <climits>
#include <cmath>
#include <csignal>
#include <cstdarg>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <memory>
#include <numeric>
#include <sstream>
#include <stdexcept>
#include <string>
#include <thread>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

#ifdef _MSC_VER
#pragma warning(disable : 4267)
#endif

#include "Base64.h"
#include <GLTFAccessor.h>
#include <GLTFAsset.h>
#include <GLTFBuffer.h>
#include <GLTFBufferView.h>
#include <GLTFMesh.h>
#include <GLTFPrimitive.h>
#include <GLTFScene.h>
#include <GLTFTargetNames.h>

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable : 4996)
#pragma warning(default : 4267)
#endif
#include "rapidjson/document.h"
#ifdef _MSC_VER
#pragma warning(pop)
#endif
#include "rapidjson/prettywriter.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/writer.h"

#include <gsl/span>

#include <coveo/enumerable.h>
#include <coveo/linq.h>

#include <maya/M3dView.h>
#include <maya/MAnimControl.h>
#include <maya/MAnimUtil.h>
#include <maya/MArgDatabase.h>
#include <maya/MArgList.h>
#include <maya/MDagModifier.h>
#include <maya/MDagPath.h>
#include <maya/MDagPathArray.h>
#include <maya/MFileIO.h>
#include <maya/MFileObject.h>
#include <maya/MFloatMatrix.h>
#include <maya/MFloatPointArray.h>
#include <maya/MFloatVectorArray.h>
#include <maya/MFnAttribute.h>
#include <maya/MFnBlendShapeDeformer.h>
#include <maya/MFnBlinnShader.h>
#include <maya/MFnCamera.h>
#include <maya/MFnComponentListData.h>
#include <maya/MFnLambertShader.h>
#include <maya/MFnMatrixData.h>
#include <maya/MFnMesh.h>
#include <maya/MFnMessageAttribute.h>
#include <maya/MFnNumericAttribute.h>
#include <maya/MFnPhongShader.h>
#include <maya/MFnSet.h>
#include <maya/MFnSingleIndexedComponent.h>
#include <maya/MFnSkinCluster.h>
#include <maya/MFnStringArrayData.h>
#include <maya/MFnTransform.h>
#include <maya/MFnTypedAttribute.h>
#include <maya/MGlobal.h>
#include <maya/MIOStream.h>
#include <maya/MImage.h>
#include <maya/MItDependencyGraph.h>
#include <maya/MItDependencyNodes.h>
#include <maya/MItGeometry.h>
#include <maya/MItMeshFaceVertex.h>
#include <maya/MItMeshPolygon.h>
#include <maya/MMatrix.h>
#include <maya/MPointArray.h>
#include <maya/MPxCommand.h>
#include <maya/MQuaternion.h>
#include <maya/MRenderSetup.h>
#include <maya/MSelectionList.h>
#include <maya/MStreamUtils.h>
#include <maya/MSyntax.h>
#include <maya/MTime.h>
#include <maya/MUuid.h>
