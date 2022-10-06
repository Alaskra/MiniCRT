#include "minicrt.h"

extern int main(int argc, char* argv[]);

void exit(int exitCode) {
    // todo: atexit() and c++ deconstructor function
    // mini_crt_call_exit_routine();
    // exit syscall number is 60
    asm( "mov %0,%%rdi \n\t"
         "mov $60,%%rax \n\t"
         "syscall \n\t"
         ::"m"(exitCode));
}

static void crt_fatal_error(const char* msg) {
    // todo: impelment printf
    // printf("fatal error: %s\n", msg);
    exit(1);
}

void mini_crt_entry() {
    int ret;
    int argc;
    char **argv;
    char* ebp_reg = 0;
    // ebp_reg = %ebp
    asm("mov %%rbp,%0 \n\t":"=r"(ebp_reg));
    argc = *(int*)(ebp_reg + 4);
    argv = (char **)(ebp_reg + 8);
    // todo: crt initialize
    // if (!mini_crt_heap_init())
        // crt_fatal_error("heap initialize failed");
    // if (!mini_crt_io_init())
        // crt_fatal_error("IO initialize failed");
    ret = main(argc, argv);
    exit(ret);
}
