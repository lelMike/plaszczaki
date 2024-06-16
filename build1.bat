@echo off

:: Define directories
set SFML_DIR=extern\SFML-2.6.1
set INCLUDE_DIR=src\include
set SRC_DIR=src\src

:: Compiler and flags
set CXX=g++
set CXXFLAGS=-std=c++17
set INCLUDE_FLAGS=-I%INCLUDE_DIR% -I%SFML_DIR%\include
set LIB_FLAGS=-L%SFML_DIR%\lib -lsfml-graphics -lsfml-window -lsfml-system

:: Source files
set SRC_FILES=%SRC_DIR%\problem1.cpp %SRC_DIR%\WorkerRelations.cpp %SRC_DIR%\GraphHandler.cpp %SRC_DIR%\BorderHandler.cpp

:: Output binary
set OUTPUT=problem1

:: Build command
%CXX% %CXXFLAGS% %INCLUDE_FLAGS% %SRC_FILES% -o %OUTPUT% %LIB_FLAGS%

:: Check for command-line argument and run the output binary with or without it
if "%1"=="" (
    %OUTPUT%
) else (
    %OUTPUT% %1
)
