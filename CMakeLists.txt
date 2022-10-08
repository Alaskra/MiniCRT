# Set the minimum version of CMake that can be used
# To find the cmake version run
# $ cmake --version
cmake_minimum_required(VERSION 3.5)

# Set the project name
project (MiniCRT)

# Add an executable
# add_library(minicrt STATIC entry.c)
# add_library(malloc STATIC malloc.c)
add_executable(hello entry.c malloc.c stdio.c string.c printf.c)
