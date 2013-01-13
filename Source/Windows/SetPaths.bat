@ECHO OFF

REM This batch file prepares the shell for use with the tools required to build
REM BrainDead

REM Make sure to only run the following once
IF DEFINED PATHS_SET GOTO done
SET PATHS_SET=TRUE

ECHO Setting path for GNU tools...
REM Add GNU Make to the default path using either the 64- or 32-bit version of
REM the Program Files directory
IF DEFINED PROGRAMFILES(X86) ( SET "PATH=%PATH%;%PROGRAMFILES(X86)%\GnuWin32\bin" ) ELSE ( SET "PATH=%PATH%;%PROGRAMFILES%\GnuWin32\bin" )

:done
