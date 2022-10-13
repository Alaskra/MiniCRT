# Set the minimum version of CMake that can be used
# To find the cmake version run
# $ cmake --version
cmake_minimum_required(VERSION 3.5)

# Set the project name
project (MiniCRT)
set(CMAKE_C_FLAGS "-nostdlib -fno-builtin -fno-stack-protector")
add_link_options(-e mini_crt_entry)

add_library(
    minicrt
    STATIC
    entry.c
    malloc.c
    stdio.c
    string.c
    printf.c
)
add_executable(test test.c)
target_link_libraries(test PRIVATE minicrt)
