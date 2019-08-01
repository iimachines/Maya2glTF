
mkdir "%~dp0/build"
cd /d "%~dp0/build"
del CMakeCache.txt
cmake -G "Visual Studio 15 2017" -T host=x64 ..
cd /d "%~dp0"
