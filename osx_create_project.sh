#!/bin/bash

if [ $# -eq 0 ] 
    then 
        echo "Usage: ./osx_create_project.sh MAYA_VERSION" 
        echo "Example: ./osx_create_project.sh 2020"
        exit 1
fi

CMAKE="cmake"

if ! [ -x "$(command -v cmake)" ]
    then
        echo "cmake command not found in PATH, assuming it is found at /Applications/CMake.app/Contents/bin/cmake" 
        CMAKE="/Applications/CMake.app/Contents/bin/cmake"
fi

$CMAKE -B "build" -G "Unix Makefiles" -D MAYA_VERSION:string=$1
