@echo off

echo Creating GLTF build folder...
cd /d %~dp0/dependencies\COLLADA2GLTF\GLTF
if errorlevel 1 goto fail

md build
cd build
if errorlevel 1 goto fail

echo Creating GLTF Visual Studio x64 solution...
cmake .. -G "Visual Studio 15 2017 Win64"
if errorlevel 1 goto fail

echo Building GLTF Visual Studio Debug/x64 solution...
msbuild /v:q /m  /clp:ErrorsOnly /p:configuration=Debug GLTF.sln
if errorlevel 1 goto fail

echo Building GLTF Visual Studio Release/x64 solution...
msbuild /v:q /m /clp:ErrorsOnly /p:configuration=Release GLTF.sln
if errorlevel 1 goto fail
 
COLOR 2F
echo Completed! :)
goto exit

:fail
COLOR 4E
echo Failed! :(

:exit
echo Press ENTER to exit
pause 
COLOR 

cd /d %~dp0
