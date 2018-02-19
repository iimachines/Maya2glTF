file(GLOB Maya2glTF_SRC
        "*.cpp"
        "*.h")

#file(GLOB ${GLTF_SRC} "${DEPENDENCY_DIR}/COLLADA2GLTF/GLTF/src/*.cpp" "${DEPENDENCY_DIR}/COLLADA2GLTF/GLTF/include/*.h")

set(SOURCE_FILES ${Maya2glTF_SRC})

find_package(Maya REQUIRED)

include_directories(${MAYA_INCLUDE_DIR})
link_directories(${MAYA_LIBRARY_DIR})

add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES})

#if(MSVC)
#    target_link_libraries(${PROJECT_NAME} ../${DEPENDENCY_DIR}/COLLADA2GLTF/GLTF)
#elseif(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
#    target_link_libraries(${PROJECT_NAME} ../${DEPENDENCY_DIR}/COLLADA2GLTF/GLTF stdc++fs)
#endif()

# GLTF
include_directories(../${DEPENDENCY_DIR}/COLLADA2GLTF/GLTF/include)
add_subdirectory(../${DEPENDENCY_DIR}/COLLADA2GLTF/GLTF)

target_link_libraries(${PROJECT_NAME} ${MAYA_LIBRARIES} ${DEPENDENCY_DIR}/COLLADA2GLTF/GLTF)

MAYA_PLUGIN(${PROJECT_NAME})
install(TARGETS ${PROJECT_NAME} ${MAYA_TARGET_TYPE} DESTINATION plug-ins)