@echo off

set INCLUDE=.
set SOURCE=src\dict.c src\routes.c src\win32.c src\response.c
set LIBS=kernel32.lib Ws2_32.lib ucrt.lib vcruntime.lib

vcvars64.bat && ^
cl /Fe:gdps.exe /Fo:obj\ /I%include% %SOURCE% /link /ENTRY:main %LIBS% && ^
gdps.exe