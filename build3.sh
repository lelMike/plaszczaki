#!/bin/bash

# Compile the C++ program using g++
g++ src\src\problem3.cpp src\src\guards.cpp src\src\route.cpp -o problem3

# Check if compilation was successful
if [ $? -ne 0 ]; then
    echo "Compilation failed"
    exit 1
fi

# Run the compiled program with the provided input and output files
./problem3
