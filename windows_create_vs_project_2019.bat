@echo off

if "%1"=="" (
    echo Please pass the Maya version you want build as an argument, e.g 2019 to build Maya 2019
    goto :error
)

if not exist "%~dp0\build" (
    mkdir "%~dp0\build"
    if errorlevel 1 goto :error
)

if exist "%~dp0\build\CMakeCache.txt" (
    del "%~dp0\build\CMakeCache.txt"
    if errorlevel 1 goto :error
)

cmake -B "%~dp0\build" -G "Visual Studio 16 2019" -T host=x64 -D MAYA_VERSION:string=%*
if errorlevel 1 goto :error

:error
