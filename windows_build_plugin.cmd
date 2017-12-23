@echo off

SET MAYA_VERSION=%1

IF "%1"=="" (SET MAYA_VERSION=2018)

echo Building Maya2glTF for Maya %MAYA_VERSION%...
cd /d %~dp0
msbuild /m /v:q /p:configuration=Maya%MAYA_VERSION%-Release
if errorlevel 1 goto fail
 
COLOR 2F
echo Completed! :)
echo.
echo The plugin and debug symbols are already copied to "%userprofile%\Documents\Maya\%MAYA_VERSION%\plug-ins\",
echo so the plugin can directly be used when you restart Maya.
echo.
goto exit

:fail
COLOR 4E
echo Failed! :(

:exit
echo Press ENTER to exit
pause 
COLOR 

cd /d %~dp0
