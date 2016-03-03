@echo off 
set PROJECT_DIR=%~dp0
set OUTDIR_ROOT=%~dp0..
cmd /c %XTERNAL%\make_one.cmd ~ dll debug %*
