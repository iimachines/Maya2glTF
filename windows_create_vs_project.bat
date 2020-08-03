@echo off
setlocal

if "%1"=="" (
    echo Please pass the Maya version you want build as an argument, e.g 2019 to build Maya 2019
    goto :error
)

set BUILD=%~dp0\build\%1

if not exist "%BUILD%" (
    mkdir "%BUILD%"
    if errorlevel 1 goto :error
)

if exist "%BUILD%\CMakeCache.txt" (
    del "%BUILD%\CMakeCache.txt"
    if errorlevel 1 goto :error
)

cmake -B "%BUILD%" -G "Visual Studio 16 2019" -T host=x64 -D MAYA_VERSION:string=%*
if errorlevel 1 goto :error

:error
