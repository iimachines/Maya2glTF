@echo off
echo Copying "%~dp0\maya" to "%userprofile%\Documents\maya"...
xcopy /y /s "%~dp0\maya" "%userprofile%\Documents\maya"
echo Done. Press ENTER to exit.
pause
