# how to use cmake to do the following things:
gcc -c -fno-builtin -nostdlib -fno-stack-protector entry.c malloc.c stdio.c string.c printf.c at_exit.c ctors.cpp crtbegin.cpp crtend.cpp
ar -rs minicrt.a malloc.o printf.o stdio.o string.o at_exit.o ctors.o
gcc -c -ggdb -fno-builtin -nostdlib -fno-stack-protector test.c
ld -static -e mini_crt_entry crtbegin.o entry.o test.o minicrt.a crtend.o -o test
