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
    if (!mini_crt_heap_init())
        crt_fatal_error("heap initialize failed");
    if (!mini_crt_io_init())
        crt_fatal_error("IO initialize failed");
    ret = main(argc, argv);
    exit(ret);
}

void print_int(unsigned i) {
    // for debug
    char a1[100]="hhhhhhhhhhhhhhhhhhh\nxxxxx";
    int idx = 0;
    while (i!=0) {
        a1[idx++] = '0'+i%10;
        i = i/10;
    }
    fwrite(a1, 1, 20, stdout);
}

void test_stdio() {
    char a1[100]="hhhhhhhhhhhhhhhhhhh\nxxxxx";
    /* FILE *fp = fopen("CMakeLists.txt", "r+"); */
    FILE *fp;
    fp = fopen("test.txt", "w+");
    fwrite("asdasdasd", 1, 9, fp);
    fclose(fp);
    fp = fopen("test.txt", "r");
    fread(a1, 1, 9, fp);
    fwrite(a1, 1, 20, stdout);
    // output: asdasdasdhhhhhhhhhh
    fclose(fp);
}

void test_string() {
    char a1[100]="hhhhhhhhhhhhhhhhhhh\n"; // 19 h
    char *t = "true\n";
    if(strlen(a1) == 20)
        fwrite(t, 1, 5, stdout);  // output: true
    itoa(12345, a1, 10);
    fwrite(a1, 1, 20, stdout);  // output: 12345
    strcpy(a1, "54321");
    fwrite(a1, 1, 20, stdout);  // output: 54321
    if(strcmp("123", "124") == -1)
        fwrite(t, 1, 5, stdout);  // output: true
}

void test_printf() {
    printf("hello %s, %d %d%d%d%d%d\n", "world", 3,2,1,6,5,4);
    // output: hello world, 3 21654
}

int main(int argc, char* argv[]){
    if (!mini_crt_heap_init())
        crt_fatal_error("heap initialize failed");
    test_stdio();
    test_string();
    test_printf();
    /* exit(0); */
}
