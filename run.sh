# how to use cmake to do the following things:
gcc -c -fno-builtin -nostdlib -fno-stack-protector entry.c malloc.c stdio.c string.c printf.c at_exit.c
g++ -c -nostdinc++ -fno-rtti -fno-exceptions -fno-builtin -nostdlib -fno-stack-protector new_delete.cpp iostream.cpp stringpp.cpp sysdep.cpp crtbegin.cpp crtend.cpp
ar -rs minicrt.a malloc.o printf.o stdio.o string.o at_exit.o new_delete.o iostream.o stringpp.o sysdep.o entry.o
gcc -c -ggdb -fno-builtin -nostdlib -fno-stack-protector test.c
g++ -c -nostdinc++ -fno-rtti -fno-exceptions -fno-builtin -nostdlib -fno-stack-protector testpp.cpp
ld -static -e mini_crt_entry crtbegin.o test.o minicrt.a crtend.o -o test
ld -static -e mini_crt_entry crtbegin.o testpp.o minicrt.a crtend.o -o testpp
