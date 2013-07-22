@echo off
setlocal ENABLEDELAYEDEXPANSION

rem for /F "delims=" %%I in ("%~dp0") do cd %%~fI
cd %~dp0

set dirs=
set target=
set _CFG=CFG=strict
set _PLATF=PLATF=win_x86

:rep
if "%1" == ""		goto :l
if "%1" == "clean"	set target=clean
if "%1" == "rebuild"	set target=clean ALL
if "%1" == "strict"	set _CFG=CFG=strict
if "%1" == "fast"	set _CFG=CFG=fast
if "%1" == "-t"		set dirs=%dirs% %2 && shift
if "%1" == "@bbk_x86"	set _PLATF=PLATF=bbk_x86
if "%1" == "@bbk_arm"	set _PLATF=PLATF=bbk_arm
if "%1" == "@win_x86"	set _PLATF=PLATF=win_x86
if "%1" == "@lin_x86"	set _PLATF=PLATF=lin_x86
shift
goto :rep

:l

if "%target%" == "" set target=ALL
if not "%dirs%" == "" goto :make

for /D %%i in (*) do set dirs=!dirs! %%i

:make
for %%i in (%dirs%) do (
    cd %%i
    echo .                                            .
    echo ----------------------------------------------
    echo .                                            .
    echo . make %target% in %%i  
    nmake /nologo %target% %_CFG% %_PLATF%
    cd ..
)  

