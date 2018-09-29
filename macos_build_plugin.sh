#!/bin/bash
set -e
mkdir -p build
cd build
if [ -f ./CMakeCache.txt ]; then
  rm ./CMakeCache.txt
fi
echo Generating Unix makefiles...
/Applications/CMake.app/Contents/bin/cmake -G "Unix Makefiles" ..
#echo Building plugin...
#make
echo Installing plugin...
make install
echo All done!
