#!/bin/bash

# Check if command-line arguments are provided
if [ -z "$1" ]; then
    echo "Error: Missing argument 1: Input file"
    exit 1
fi

if [ -z "$2" ]; then
    echo "Error: Missing argument 2: Output file"
    exit 1
fi

# Compile the C++ program using g++
g++ src\src\problem2.cpp -o problem2

# Check if compilation was successful
if [ $? -ne 0 ]; then
    echo "Compilation failed"
    exit 1
fi

# Run the compiled program with the provided input and output files
./problem2 $1 $2
