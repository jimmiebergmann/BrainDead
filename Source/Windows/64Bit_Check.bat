@echo off
cl /? 2>&1 | findstr /C:"x64" > nul && goto FOUND
EXIT /B 0
:FOUND
EXIT /B 1
