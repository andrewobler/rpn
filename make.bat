@echo off
rem Simple Makefile equivalent for RPN

echo Executing make...

:: Get task from command line
set task=%1

if "%task%"=="all" goto all
if "%task%"=="" goto all

if "%task%"=="clean" goto clean

:: Builds all files
:all
    echo Building all...
    cl /EHsc winmain.cpp rpn_stack.cpp /Fe"build.exe" /link user32.lib
    goto finish

:: Deletes all executables and object files
:clean
    echo Cleaning up...
    del *.obj *.exe
    goto finish

:: Prints leave message
:finish
    echo Task complete, exiting...
