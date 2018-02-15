cmake_minimum_required(VERSION 3.9)
project(Maya2glTF)

# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

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
file(GLOB GLTF_SRC
    "${DEPENDENCY_DIR}/COLLADA2GLTF/GLTF/src/*.cpp"
    "${DEPENDENCY_DIR}/COLLADA2GLTF/GLTF/include/*.h")
add_library(GLTF STATIC ${GLTF_SRC})
target_include_directories(GLTF PUBLIC include)

# RapidJSON
include_directories(SYSTEM ${DEPENDENCY_DIR}/COLLADA2GLTF/GLTF/dependencies/rapidjson/include)

# DRACO
add_definitions(-DDRACO_POINT_CLOUD_COMPRESSION_SUPPORTED)
include_directories(${DEPENDENCY_DIR}/COLLADA2GLTF/GLTF/dependencies/draco/src)
add_subdirectory(${DEPENDENCY_DIR}/COLLADA2GLTF/GLTF/dependencies/draco)
# file(GLOB DRACO_SRC
#     "${DEPENDENCY_DIR}/COLLADA2GLTF/GLTF/dependencies/draco/src/draco/*/*.cc"
# "${DEPENDENCY_DIR}/COLLADA2GLTF/GLTF/dependencies/draco/src/draco/*/*.h")
# add_library(DRACO STATIC ${DRACO_SRC})

# COVEO
include_directories(SYSTEM ${DEPENDENCY_DIR}/cpp-linq/lib)

# GSL
include_directories(${DEPENDENCY_DIR}/GSL/include)

# Maya2glTF
#add_subdirectory(src)
file(GLOB Maya2glTF_SRC
        "src/*.cpp"
        "include/*.h")

# file(GLOB ${GLTF_SRC} "${DEPENDENCY_DIR}/COLLADA2GLTF/GLTF/src/*.cpp" "${DEPENDENCY_DIR}/COLLADA2GLTF/GLTF/include/*.h")

set(SOURCE_FILES ${Maya2glTF_SRC})

find_package(Maya REQUIRED)

include_directories(${MAYA_INCLUDE_DIR})
link_directories(${MAYA_LIBRARY_DIR})

add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} ${MAYA_LIBRARIES} ${draco_LIBRARIES} GLTF draco)
# target_link_libraries(${PROJECT_NAME} ${GLTF_LIBRARY})

MAYA_PLUGIN(${PROJECT_NAME})

install(TARGETS ${PROJECT_NAME} ${MAYA_TARGET_TYPE} DESTINATION plug-ins)
