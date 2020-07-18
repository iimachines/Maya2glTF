call windows_create_vs_project_2019.bat %1
call msbuild /m /p:configuration=Release build\%1\maya2glTF.sln
