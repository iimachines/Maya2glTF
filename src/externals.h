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

#include <gsl/span>

#include <experimental/vector>
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

