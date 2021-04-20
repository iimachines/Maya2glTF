@echo off

setlocal 

cd /d %~dp0

FOR /F "tokens=*" %%g IN ('git tag -l --points-at HEAD') do (SET GIT_TAG=%%g)
FOR /F "tokens=*" %%g IN ('git rev-parse --short HEAD') do (SET GIT_REV=%%g)

ECHO GIT_TAG = %GIT_TAG%
ECHO GIT_REV = %GIT_REV%
set ZIP_PATH=%~dp0build\maya2gltf_%GIT_TAG%_%GIT_REV%.zip
if exist %ZIP_PATH% (del %ZIP_PATH%)

echo Creating release %ZIP_PATH%

start "Maya2glTF_build_2017" call windows_build_release 2017 AUTO
start "Maya2glTF_build_2018" call windows_build_release 2018 AUTO
start "Maya2glTF_build_2019" call windows_build_release 2019 AUTO
start "Maya2glTF_build_2020" call windows_build_release 2020 AUTO
start "Maya2glTF_build_2022" call windows_build_release 2022 AUTO

:loop
echo Waiting for build processes to finish...
timeout /t 10 >nul
tasklist /v /fi "imagename eq cmd.exe" /fo csv | findstr /i "Maya2glTF_build" >nul && goto :loop

pushd build
echo Creating release ZIP file...
cmake -E tar cfv %ZIP_PATH% --format=zip redist
popd

:done

endlocal
