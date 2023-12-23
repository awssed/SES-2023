@echo off
 call vcvarsall.bat x86 
ml /c in.asm
link in.obj /SUBSYSTEM:CONSOLE
call in.exe