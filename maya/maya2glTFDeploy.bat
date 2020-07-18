@echo off
setlocal
FOR /F "tokens=3 delims= " %%G IN ('REG QUERY "HKCU\Software\Microsoft\Windows\CurrentVersion\Explorer\Shell Folders" /v "Personal"') DO (SET USER_DOCUMENTS=%%G)
echo Copying "package" to "%USER_DOCUMENTS%\maya"...
robocopy "package" "%USER_DOCUMENTS%\maya" /E
echo Done. Press ENTER to exit.
endlocal
pause
