@echo off
 call C:Program FilesMicrosoft Visual Studio‚2CommunityVCAuxiliaryBuildcvarsall.bat x86
 ml / c in.asm
link in.obj /SUBSYSTEM:CONSOLE
call in.exe