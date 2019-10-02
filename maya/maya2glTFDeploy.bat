@echo off
echo Copying "." to "%userprofile%\Documents\maya"...
robocopy "." "%userprofile%\Documents\maya" /E
echo Done. Press ENTER to exit.
pause
