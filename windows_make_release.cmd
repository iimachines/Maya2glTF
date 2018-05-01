@echo off

set PROJECT_DIR=%~dp0

cd /d "%userprofile%\Documents"

del /q "Maya\2017\plug-ins\Maya2glTF*"
del /q "Maya\2017\scripts\Maya2glTF*"
del /q "Maya\2018\plug-ins\Maya2glTF*"
del /q "Maya\2018\scripts\Maya2glTF*"

cd /d "%PROJECT_DIR%"

del /q "build\Maya2glTF*.zip"

msbuild /v:q /p:Configuration=Maya2017-Release /p:Platform=x64 maya2glTF.sln 
if errorlevel 1 goto :error

msbuild /v:q /p:configuration=Maya2018-Release /p:Platform=x64 maya2glTF.sln 
if errorlevel 1 goto :error

cd /d "%userprofile%\Documents"

"c:\Program Files\WinRAR\rar.exe" A "%~dp0\build\Maya2glTF_v0.9.4-beta.zip" "Maya\2017\plug-ins\Maya2glTF*" "Maya\2017\scripts\Maya2glTF*" "Maya\2018\plug-ins\Maya2glTF*" "Maya\2018\scripts\Maya2glTF*"

if errorlevel 1 goto :error

cd /d "%PROJECT_DIR%\Maya"
"c:\Program Files\WinRAR\rar.exe" A "%~dp0\build\Maya2glTF_v0.9.4-beta.zip" deploy.bat

echo ### SUCCESS ###
pause
goto :exit

:error
echo *** FAILED ***
pause

:exit
cd /d "%PROJECT_DIR%"
