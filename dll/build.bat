@echo off

set LIBS=user32.lib kernel32.lib ucrt.lib
set GD=F:\gd\2.113\
set BIN=gdps.dll

vcvars32.bat && ^
cl /LD /Fe:%BIN% /Fo:obj\ dll.c /link /ENTRY:DllMain /SUBSYSTEM:windows %LIBS% && ^
copy /y %BIN% /b %GD%