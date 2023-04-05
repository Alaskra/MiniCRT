cmake_minimum_required(VERSION 3.12)

project(MiniCRT)

set(coptions "-fno-builtin;-nostdlib;-fno-stack-protector")
set(cppoptions "-nostdinc++;-fno-rtti;-fno-exceptions;-fno-builtin;-nostdlib;-fno-stack-protector")
set(cfiles "entry.c;malloc.c;stdio.c;string.c;printf.c;at_exit.c")
set(cppfiles "new_delete.cpp;iostream.cpp;stringpp.cpp;sysdep.cpp")

add_library(crtbegin OBJECT crtbegin.cpp)
target_compile_options(crtbegin PRIVATE ${cppoptions})

add_library(crtend OBJECT crtend.cpp)
target_compile_options(crtend PRIVATE ${cppoptions})

add_library(minicrtc OBJECT ${cfiles})
target_compile_options(minicrtc PRIVATE ${coptions})

add_library(minicrtcpp OBJECT ${cppfiles})
target_compile_options(minicrtcpp PRIVATE ${cppoptions})

add_library(minicrt STATIC $<TARGET_OBJECTS:minicrtc> $<TARGET_OBJECTS:minicrtcpp>)

add_executable(test)
add_library(testo OBJECT test.c)
target_compile_options(testo PRIVATE ${coptions} -ggdb)
target_link_libraries(test crtbegin testo minicrtc minicrtcpp crtend)
target_link_options(test PRIVATE "-Wl,-static,-e,mini_crt_entry" ${coptions})

add_executable(testpp)
add_library(testppo OBJECT testpp.cpp)
target_compile_options(testppo PRIVATE ${cppoptions})
# when use minicrt, the libminicrt.a will append to the end of linker, why?
# target_link_libraries(testpp crtbegin testppo minicrt crtend)
target_link_libraries(testpp crtbegin testppo minicrtc minicrtcpp crtend)
target_link_options(testpp PRIVATE "-Wl,-static,-e,mini_crt_entry" ${cppoptions})
