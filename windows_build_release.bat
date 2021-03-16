call windows_create_vs_project.bat %1
if errorlevel 1 goto :fail

call msbuild /m:4 /p:configuration=Release build\%1\maya2glTF.sln
if errorlevel 1 goto :fail

xcopy /s /e /y build\%1\redist\*.* build\redist\
if errorlevel 1 goto :fail

exit

:fail
echo *** FAILURE ***
