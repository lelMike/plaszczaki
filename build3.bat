@echo off

REM Compile the C++ program using g++
g++ src\src\problem3.cpp src\src\guards.cpp src\src\route.cpp -o problem3

REM Check if compilation was successful
IF %errorlevel% neq 0 (
    echo Compilation failed
    exit /b 1
)

REM Run the compiled program with the provided input and output files
problem3

exit /b 0
