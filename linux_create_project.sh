#!/bin/bash

if [ $# -eq 0 ] 
    then 
        echo "Usage: ./linux_create_project.sh MAYA_VERSION" 
        echo "Example: ./linux_create_project.sh 2020"
        exit 1
fi

cmake3 -B "build" -G "Unix Makefiles" -D MAYA_VERSION:string=$1
