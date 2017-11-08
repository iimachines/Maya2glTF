#pragma once

#include <iostream>
#include <sstream>
#include <cassert>
#include <vector>
#include <algorithm>
#include <array>

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
