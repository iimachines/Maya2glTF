@echo off
:: Direct paths provided by user
SET "MAYA_VERSION=2026"
SET "MAYA_DEVKIT_BASE=C:\Users\gerar\Desktop\SOFTWARE\Autodesk_Maya_2026_DEVKIT_Windows\devkitBase\devkit"
SET "MAYA_LOCATION=C:\Program Files\Autodesk\Maya2026"

:: Set Environment Variables
SET "MAYA_LOCATION_%MAYA_VERSION%=%MAYA_LOCATION%"
SET "MAYA_DEVKIT_BASE_RELEASE=%MAYA_DEVKIT_BASE%"

:: Clean and recreate build directory to ensure a fresh start
IF EXIST "build_%MAYA_VERSION%" rd /s /q "build_%MAYA_VERSION%"
mkdir "build_%MAYA_VERSION%"
cd "build_%MAYA_VERSION%"

echo Generating Visual Studio 2022 Project with Compatibility Flags...
:: Added -DCMAKE_POLICY_VERSION_MINIMUM=3.5 to fix the GSL/COLLADA error
cmake -G "Visual Studio 17 2022" -A x64 ^
    -DCMAKE_POLICY_VERSION_MINIMUM=3.5 ^
    -DMAYA_VERSION=%MAYA_VERSION% ^
    -DMAYA_INSTALL_BASE_DEFAULT="%MAYA_LOCATION%" ^
    -DMAYA_DEVKIT_BASE_RELEASE="%MAYA_DEVKIT_BASE%" ^
    ..

if %ERRORLEVEL% NEQ 0 (
    echo CMake generation failed.
    pause
    exit /b %ERRORLEVEL%
)

echo.
echo Starting Build (Release Configuration)...
cmake --build . --config Release

if %ERRORLEVEL% NEQ 0 (
    echo.
    echo Build failed. If errors persist, we may need to patch the GSL CMakeLists.txt manually.
    pause
    exit /b %ERRORLEVEL%
)

echo.
echo Build Successful! 
pause