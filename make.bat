@echo off
setlocal

set MAIN=%1
set NAME=%2

g++ %MAIN% -o %NAME%
start %NAME%