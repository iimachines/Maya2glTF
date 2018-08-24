cmake_minimum_required(VERSION 3.8)

project(maya2glTF)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/modules")

find_package(Maya REQUIRED)

include(ExternalProject)

# COLLADA2GLTF
# We only need to build the GLTF sub-library, hence the SOURCE_SUBDIR
ExternalProject_Add(COLLADA2GLTF
  GIT_REPOSITORY https://github.com/WonderMediaProductions/COLLADA2GLTF
  GIT_TAG maya2glTF
  PREFIX COLLADA2GLTF
  SOURCE_SUBDIR GLTF
  INSTALL_DIR
  CMAKE_ARGS
  -DCMAKE_INSTALL_PREFIX=<INSTALL_DIR>
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
  CMAKE_ARGS
	-DCMAKE_INSTALL_PREFIX=<INSTALL_DIR>
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
#message("Using ${binary_dir}/${CMAKE_BUILD_TYPE} as GLTF target folder")
set(GLTF_LIBRARY_DIR "${binary_dir}/${CMAKE_BUILD_TYPE}") 
set(DRACO_LIBRARY_DIR "${binary_dir}/dependencies/draco/${CMAKE_BUILD_TYPE}") 

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

target_link_libraries(${PROJECT_NAME} ${MAYA_LIBRARIES} glTF draco)

if(MSVC)
  
  add_custom_command(TARGET maya2glTF POST_BUILD 
    COMMAND XCOPY /Y "$<SHELL_PATH:$<TARGET_FILE:maya2glTF>>" "$<SHELL_PATH:$ENV{USERPROFILE}/Documents/maya/${MAYA_VERSION}/plug-ins/>"
    COMMAND xcopy /y "$<SHELL_PATH:${PROJECT_SOURCE_DIR}/maya/scripts/maya2glTF*.mel>" "$<SHELL_PATH:$ENV{USERPROFILE}/Documents/maya/${MAYA_VERSION}/scripts/>"
    COMMAND xcopy /y /s /i "$<SHELL_PATH:${PROJECT_SOURCE_DIR}/maya/renderData/*.*>" "$<SHELL_PATH:$ENV{USERPROFILE}/Documents/maya/maya2glTF/PBR/>"
  )

endif()

MAYA_PLUGIN(${PROJECT_NAME})
