cmake_minimum_required(VERSION 3.9)
project(Maya2glTF)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC -Wextra")

if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17")
else()
    set(CMAKE_CXX_STANDARD 17)
endif(MSVC)

set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_BINARY_DIR}/install)
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/modules)

set(DEPENDENCY_DIR dependencies)

# GLTF
include_directories(${DEPENDENCY_DIR}/COLLADA2GLTF/GLTF/include)
add_subdirectory(${DEPENDENCY_DIR}/COLLADA2GLTF/GLTF)

# RapidJSON
include_directories(${DEPENDENCY_DIR}/COLLADA2GLTF/GLTF/dependencies/rapidjson/include)

# COVEO
include_directories(${DEPENDENCY_DIR}/cpp-linq/lib)

# GSL
include_directories(${DEPENDENCY_DIR}/GSL/include)

# DRACO
include_directories(${DEPENDENCY_DIR}/COLLADA2GLTF/GLTF/dependencies/draco/src)

# Maya2glTF
add_subdirectory(src)
