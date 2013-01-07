@echo off
cl /? 2>&1 | findstr /C:"x64" > nul && goto FOUND
ECHO 0
:FOUND
ECHO 1
