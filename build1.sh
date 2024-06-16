#!/bin/bash

# Define directories
SFML_DIR="extern/SFML-2.6.1"
INCLUDE_DIR="src/include"
SRC_DIR="src/src"

# Compiler and flags
CXX=g++
CXXFLAGS="-std=c++17"
INCLUDE_FLAGS="-I$INCLUDE_DIR -I$SFML_DIR/include"
LIB_FLAGS="-L$SFML_DIR/lib -lsfml-graphics -lsfml-window -lsfml-system"

# Source files
SRC_FILES="$SRC_DIR/problem1.cpp $SRC_DIR/WorkerRelations.cpp $SRC_DIR/GraphHandler.cpp $SRC_DIR/BorderHandler.cpp"

# Output binary
OUTPUT="problem1"

# Build command
$CXX $CXXFLAGS $INCLUDE_FLAGS $SRC_FILES -o $OUTPUT $LIB_FLAGS

# Check for command-line argument and run the output binary with or without it
if [ -z "$1" ]; then
    ./$OUTPUT
else
    ./$OUTPUT "$1"
fi
