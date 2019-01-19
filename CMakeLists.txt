cmake_minimum_required(VERSION 3.8)

project(maya2glTF)

if(NOT WIN32)
  string(ASCII 27 Esc)
  set(ColourReset "${Esc}[m")
  set(ColourBold  "${Esc}[1m")
  set(Red         "${Esc}[31m")
  set(Green       "${Esc}[32m")
  set(Yellow      "${Esc}[33m")
  set(Blue        "${Esc}[34m")
  set(Magenta     "${Esc}[35m")
  set(Cyan        "${Esc}[36m")
  set(White       "${Esc}[37m")
  set(BoldRed     "${Esc}[1;31m")
  set(BoldGreen   "${Esc}[1;32m")
  set(BoldYellow  "${Esc}[1;33m")
  set(BoldBlue    "${Esc}[1;34m")
  set(BoldMagenta "${Esc}[1;35m")
  set(BoldCyan    "${Esc}[1;36m")
  set(BoldWhite   "${Esc}[1;37m")
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/modules")

if (NOT DEFINED MAYA_VERSION)
  set(MAYA_VERSION $ENV{MAYA_VERSION})
  if (NOT MAYA_VERSION)
    set(MAYA_VERSION 2018 CACHE STRING "Maya version")
  endif()
endif()

message (STATUS "${BoldMagenta}Using Maya version " ${MAYA_VERSION} "${ColourReset}")

find_package(Maya REQUIRED)

include(ExternalProject)

# COLLADA2GLTF
# We only need to build the GLTF sub-library, hence the SOURCE_SUBDIR
ExternalProject_Add(COLLADA2GLTF
  GIT_REPOSITORY https://github.com/WonderMediaProductions/COLLADA2GLTF
  GIT_TAG master
  PREFIX COLLADA2GLTF
  SOURCE_SUBDIR GLTF
  INSTALL_DIR
  CMAKE_ARGS -Dtest=false -DTEST_ENABLED=false
  -DCMAKE_INSTALL_PREFIX=<INSTALL_DIR>
  PATCH_COMMAND ${CMAKE_COMMAND} -E remove_directory "${CMAKE_BINARY_DIR}/COLLADA2GLTF/src/COLLADA2GLTF/dependencies"
  #CONFIGURE_COMMAND ${CMAKE_COMMAND} -DCMAKE_INSTALL_PREFIX:PATH=<INSTALL_DIR> <SOURCE_DIR>/GLTF  
)


# cpp-linq
ExternalProject_Add(linq
  GIT_REPOSITORY https://github.com/coveo/linq.git
  GIT_TAG v2.0.2
  PREFIX linq
  INSTALL_DIR
  CMAKE_ARGS
  -DCMAKE_INSTALL_PREFIX=<INSTALL_DIR>
  CONFIGURE_COMMAND ""
  BUILD_COMMAND ""
  INSTALL_COMMAND ""
)

# GSL
ExternalProject_Add(GSL
  GIT_REPOSITORY https://github.com/Microsoft/GSL.git
  GIT_TAG v1.0.0
  PREFIX GSL
  INSTALL_DIR
  CMAKE_ARGS -DGSL_TEST=false
	-DCMAKE_INSTALL_PREFIX=<INSTALL_DIR>
  PATCH_COMMAND ${CMAKE_COMMAND} -E remove_directory "${CMAKE_BINARY_DIR}/GSL/src/GSL/tests"
)

# filesystem
ExternalProject_Add(filesystem
  GIT_REPOSITORY https://github.com/WonderMediaProductions/filesystem
  GIT_TAG maya2glTF
  PREFIX filesystem
  INSTALL_DIR
  CMAKE_ARGS
	-DCMAKE_INSTALL_PREFIX=<INSTALL_DIR>
  CONFIGURE_COMMAND ""
  BUILD_COMMAND ""
  INSTALL_COMMAND ""
)


set(GLTF_INCLUDE_DIR          "${CMAKE_BINARY_DIR}/COLLADA2GLTF/src/COLLADA2GLTF/GLTF/include")
set(DRACO_INCLUDE_DIR         "${CMAKE_BINARY_DIR}/COLLADA2GLTF/src/COLLADA2GLTF/GLTF/dependencies/draco/src")
set(RAPIDJSON_INCLUDE_DIR     "${CMAKE_BINARY_DIR}/COLLADA2GLTF/src/COLLADA2GLTF/GLTF/dependencies/rapidjson/include")
#set(COLLADA2GLTF_INCLUDE_DIR  "${CMAKE_BINARY_DIR}/COLLADA2GLTF/include")
set(GSL_INCLUDE_DIR           "${CMAKE_BINARY_DIR}/GSL/include")
set(LINQ_INCLUDE_DIR          "${CMAKE_BINARY_DIR}/linq/src/linq/lib")
set(FS_INCLUDE_DIR            "${CMAKE_BINARY_DIR}/filesystem/src/filesystem")

# TODO: It seems the gltf.lib is not installed by COLLADA2GLTF, although draco.lib is? Figure out why
ExternalProject_Get_Property(COLLADA2GLTF binary_dir)
message("Using ${binary_dir} as GLTF target folder")
set(GLTF_LIBRARY_DIR "${binary_dir}") 
set(DRACO_LIBRARY_DIR "${binary_dir}/dependencies/draco") 

file(GLOB SOURCES "src/*.cpp" "src/*.h" "src/*.c")

if (MSVC)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Yuexternals.h")
  set_source_files_properties(src/externals.cpp PROPERTIES COMPILE_FLAGS "/Ycexternals.h")
  set_source_files_properties(src/mikktspace.c  PROPERTIES COMPILE_FLAGS "/Y-")
endif()

include_directories(
  ${GLTF_INCLUDE_DIR}
  ${DRACO_INCLUDE_DIR}
  ${RAPIDJSON_INCLUDE_DIR}
  ${GSL_INCLUDE_DIR}
  ${MAYA_INCLUDE_DIR}
  ${LINQ_INCLUDE_DIR}
  ${FS_INCLUDE_DIR}
)

link_directories(
  ${MAYA_LIBRARY_DIR}
  ${GLTF_LIBRARY_DIR}
  ${DRACO_LIBRARY_DIR}
)

add_library(${PROJECT_NAME} SHARED ${SOURCES})

add_dependencies(${PROJECT_NAME}
  GSL
  COLLADA2GLTF
  linq
  filesystem
)

target_link_libraries(${PROJECT_NAME} ${MAYA_LIBRARIES} GLTF draco)

# Get the current working branch
execute_process(
  COMMAND git rev-parse --abbrev-ref HEAD
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
  OUTPUT_VARIABLE GIT_BRANCH
  OUTPUT_STRIP_TRAILING_WHITESPACE
)

# Get the current tag
execute_process(
  COMMAND git describe --tags --abbrev=0
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
  OUTPUT_VARIABLE GIT_TAG
  OUTPUT_STRIP_TRAILING_WHITESPACE
)

# Get the latest abbreviated commit hash of the working branch
execute_process(
  COMMAND git log -1 --format=%h
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
  OUTPUT_VARIABLE GIT_COMMIT_HASH
  OUTPUT_STRIP_TRAILING_WHITESPACE
)

configure_file(
  ${CMAKE_SOURCE_DIR}/version.inl.in
  ${CMAKE_BINARY_DIR}/generated/version.inl
)

configure_file(
  ${CMAKE_SOURCE_DIR}/version.mel.in
  ${CMAKE_BINARY_DIR}/generated/maya2glTF_version.mel
)

include_directories(${CMAKE_BINARY_DIR}/generated)

if(MSVC)
  
  add_custom_command(TARGET maya2glTF POST_BUILD 
    COMMAND XCOPY /Y "$<SHELL_PATH:$<TARGET_FILE:maya2glTF>>" "$<SHELL_PATH:$ENV{USERPROFILE}/Documents/maya/${MAYA_VERSION}/plug-ins/>"
    COMMAND xcopy /y "$<SHELL_PATH:${PROJECT_SOURCE_DIR}/maya/scripts/maya2glTF*.mel>" "$<SHELL_PATH:$ENV{USERPROFILE}/Documents/maya/${MAYA_VERSION}/scripts/>"
    COMMAND xcopy /y /s /i "$<SHELL_PATH:${PROJECT_SOURCE_DIR}/maya/renderData/*.*>" "$<SHELL_PATH:$ENV{USERPROFILE}/Documents/maya/maya2glTF/PBR/>"
  )

elseif(APPLE)

  install (
    TARGETS maya2glTF 
    DESTINATION "/Users/Shared/Autodesk/maya/${MAYA_VERSION}/plug-ins/"
  )
  
  install (
    DIRECTORY "${PROJECT_SOURCE_DIR}/maya/scripts/" 
    DESTINATION "/Users/Shared/Autodesk/maya/scripts"
    FILES_MATCHING PATTERN "maya2glTF*.mel"
  )

  install (
    DIRECTORY "${CMAKE_BINARY_DIR}/generated/" 
    DESTINATION "/Users/Shared/Autodesk/maya/scripts"
    FILES_MATCHING PATTERN "maya2glTF*.mel"
  )

  install (
    DIRECTORY "${PROJECT_SOURCE_DIR}/maya/renderData/"
    DESTINATION "/Users/Shared/Autodesk/maya/maya2glTF/PBR"
  )

endif()

MAYA_PLUGIN(${PROJECT_NAME})
