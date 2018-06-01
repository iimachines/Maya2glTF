@echo off

cd /d "%userprofile%\Documents\Maya"
if errorlevel 1 goto :error

del /q /s Maya2glTF*

cd /d "%~dp0\build"
if errorlevel 1 goto :error

del /q "Maya2glTF*.zip"
rd /s /q Maya2glTF

mkdir Maya2glTF
if errorlevel 1 goto :error

cd /d "%~dp0"
xcopy /y Maya\deploy.bat build\Maya2glTF
if errorlevel 1 goto :error

msbuild /v:q /p:Configuration=Maya2017-Release /p:Platform=x64 maya2glTF.sln 
if errorlevel 1 goto :error

msbuild /v:q /p:configuration=Maya2018-Release /p:Platform=x64 maya2glTF.sln 
if errorlevel 1 goto :error

cd /d "%~dp0\build"
if errorlevel 1 goto :error

xcopy /y /s "%userprofile%\Documents\Maya\Maya2glTF*" "Maya2glTF\Maya\"
if errorlevel 1 goto :error

xcopy /y /s /i "%userprofile%\Documents\Maya\Maya2glTF" "Maya2glTF\Maya\Maya2glTF"
if errorlevel 1 goto :error

where dos2unix
if errorlevel 0 (
    echo Removing BOM from UTF-8 files
    for /r %%f in (*.mel) do (dos2unix %%f)
)

"c:\Program Files\WinRAR\rar.exe" A -r "Maya2glTF_v0.9.6-beta.zip" "Maya2glTF\*" 
if errorlevel 1 goto :error

echo ### SUCCESS ###
pause
goto :exit

:error
echo *** FAILED ***
pause

:exit
cd /d "%~dp0"