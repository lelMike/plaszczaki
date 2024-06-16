@echo off

REM Check if command-line arguments are provided
IF "%1"=="" (
    echo Error: Missing argument 1: Input file
    exit /b 1
)

IF "%2"=="" (
    echo Error: Missing argument 2: Output file
    exit /b 1
)

REM Compile the C++ program using g++
g++ src\src\problem2.cpp -o problem2

REM Check if compilation was successful
IF %errorlevel% neq 0 (
    echo Compilation failed
    exit /b 1
)

REM Run the compiled program with the provided input and output files
problem2 %1 %2

exit /b 0
