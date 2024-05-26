@echo off

set INCLUDE=C:\vcpkg\installed\x64-windows\include
set SOURCE=src\win32.c
set LIBS=kernel32.lib Ws2_32.lib ucrt.lib vcruntime.lib

vcvars64.bat && ^
cl /Fe:gdps.exe /Fo:obj\ /I%include% %SOURCE% /link /ENTRY:main %LIBS%