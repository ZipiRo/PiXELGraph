# Build Instructions

To compile and run the program, ensure you have the following prerequisites and follow the provided steps:

##
- Make sure you use console host as the default CMD, for this to work as it should. 
- Or run the build as administrator. 

## Prerequisites
1. Install the **MinGW compiler**.
2. Set an **environment variable** for the MinGW binary directory to allow `g++` to be accessed globally.

### Setting the Environment Variable (Windows)
- Locate your MinGW installation directory (e.g., `C:\MinGW\bin`).
- Add the path to the **System Environment Variables**:
  1. Open "System Properties."
  2. Navigate to the "Advanced" tab and click on "Environment Variables."
  3. Under "System Variables," find `Path` and click "Edit."
  4. Add your MinGW `bin` directory path (e.g., `C:\MinGW\bin`).
  5. Save and restart your command prompt or system.

## Makefile (`make.bat`)

The following batch file automates the process of building and running the program.  

### Script: `make.bat`
```bat
@echo off
setlocal

set MAIN=%1
set NAME=%2

g++ %MAIN% -o %NAME%
start Build/%NAME%
```
Command example `make main.cpp main`
