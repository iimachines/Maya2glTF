
if (NOT DEFINED MAYA_VERSION)
  set(MAYA_VERSION 2018 CACHE STRING "Maya version")
endif()

set(MAYA_COMPILE_DEFINITIONS "REQUIRE_IOSTREAM;_BOOL")
set(MAYA_INSTALL_BASE_SUFFIX "")
set(MAYA_LIB_SUFFIX "lib")
set(MAYA_INC_SUFFIX "include")

if (WIN32)
  # Windows
  set(MAYA_INSTALL_BASE_DEFAULT "C:/Program Files/Autodesk")
  set(OPENMAYA OpenMaya.lib)
  set(MAYA_COMPILE_DEFINITIONS "${MAYA_COMPILE_DEFINITIONS};NT_PLUGIN")
  set(MAYA_PLUGIN_EXTENSION ".mll")
elseif(APPLE)
  # Mac
  set(MAYA_INSTALL_BASE_DEFAULT "/Applications/Autodesk")
  set(OPENMAYA libOpenMaya.dylib)
  set(MAYA_LIB_SUFFIX "Maya.app/Contents/MacOS")
  set(MAYA_INC_SUFFIX "devkit/include")
  set(MAYA_COMPILE_DEFINITIONS "${MAYA_COMPILE_DEFINITIONS};OSMac_")
  set(MAYA_PLUGIN_EXTENSION ".bundle")
else()
  # Linux
  set(MAYA_INSTALL_BASE_DEFAULT "/usr/autodesk")
  set(MAYA_INSTALL_BASE_SUFFIX -x64)
  set(OPENMAYA libOpenMaya.so)
  set(MAYA_PLUGIN_EXTENSION ".so")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS" -fPIC)
endif()

set(MAYA_INSTALL_BASE_PATH ${MAYA_INSTALL_BASE_DEFAULT} CACHE STRING "Root Maya installation path")
set(MAYA_LOCATION ${MAYA_INSTALL_BASE_PATH}/maya${MAYA_VERSION}${MAYA_INSTALL_BASE_SUFFIX})

find_path(MAYA_LIBRARY_DIR OpenMaya.lib
  PATHS
    ${MAYA_LOCATION}
    $ENV{MAYA_VERSION}
  PATH_SUFFIXES
    "${MAYA_LIB_SUFFIX}/"
  DOC "Maya library path"
)

find_path(MAYA_INCLUDE_DIR maya/Mfn.h
  PATHS
    ${MAYA_LOCATION}
    $ENV{MAYA_VERSION}
  PATH_SUFFIXES
    "${MAYA_INC_SUFFIX}/"
  DOC "Maya include path"
)

set(_MAYA_LIBRARIES OpenMaya OpenMayaAnim OpenMayaFX OpenMayaRender OpenMayaUI Foundation)
foreach(MAYA_LIB ${_MAYA_LIBRARIES})
  find_library(MAYA_${MAYA_LIB}_LIBRARY NAMES ${MAYA_LIB} PATHS ${MAYA_LIBRARY_DIR} NO_DEFAULT_PATH)
  set(MAYA_LIBRARIES ${MAYA_LIBRARIES} ${MAYA_${MAYA_LIB}_LIBRARY})
endforeach()

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(Maya DEFAULT_MSG MAYA_INCLUDE_DIR MAYA_LIBRARIES)

function(MAYA_PLUGIN _target)
  if (WIN32)
    set_target_properties(${_target} PROPERTIES
      LINK_FLAGS "/export:initializePlugin /export:uninitializePlugin"
    )
  endif()

  set_target_properties(${_target} PROPERTIES
    COMPILE_DEFINITIONS "${MAYA_COMPILE_DEFINITIONS}"
    PREFIX ""
    SUFFIX ${MAYA_PLUGIN_EXTENSION}
  )
endfunction()