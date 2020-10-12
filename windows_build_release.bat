call windows_create_vs_project.bat %1
call msbuild /m /p:configuration=Release build\%1\maya2glTF.sln
xcopy /s /e /y build\%1\redist\*.* build\redist\