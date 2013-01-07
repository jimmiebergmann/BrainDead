@echo off
FOR /L %%G IN (10,1,%1) DO cl /? 2>&1 | findstr /C:"Version %%G" > nul && goto FOUND
EXIT /B 0
:FOUND
EXIT /B 1

