@ECHO off
SET "Find=Source\Windows"
SET "Replace="
SET "OldPath=%~1"
CALL SET "NewPath=%%OldPath:\%Find%=%Replace%%%"
ECHO %NewPath%
