@echo off

set INCLUDE=C:\vcpkg\installed\x64-windows\include
set SOURCE=src\*
set LIBS=ucrt.lib kernel32.lib

vcvars64.bat && ^
cl /Fe:gdps.exe /Fo:obj\ /I%include% %SOURCE% /link /ENTRY:main %LIBS%