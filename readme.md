You'll need mingw compiler and set an eviorment variable for the binary of the compiler

MAKE --------------------- make.bat
@echo off
setlocal

set MAIN=%1
set NAME=%2

g++ %MAIN% -o Build/%NAME%
start Build/%NAME%
--------------------------