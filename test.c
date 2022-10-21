#include "minicrt.h"

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

void test_example(int argc, char* argv[]) {
    FILE *fp;
    char **v = malloc(argc*sizeof(char*));
    for(int i = 0; i < argc; i++) {
        v[i] = malloc(strlen(argv[i])*sizeof(char *));
        strcpy(v[i], argv[i]);
    }
    fp = fopen("test.txt", "w");
    for (int i=0; i<argc; i++) {
        fwrite(v[i], 1, strlen(v[i]), fp);
        fwrite("\n", 1, 1, fp);
    }
    fclose(fp);
    fp = fopen("test.txt", "r");
    char c;
    while ((fread(&c, 1, sizeof(char), fp)) != 0) {
        fputc(c, stdout);
    }
    fclose(fp);
}

void print_exit() {
    printf("exit!\n");
}

void print_exit1() {
    printf("exit1!\n");
}

void test_atexit() {
    atexit(print_exit);
    atexit(print_exit1);
}

int main(int argc, char* argv[]){
    /* test_stdio(); */
    /* test_string(); */
    /* test_printf(); */
    test_example(argc, argv);
    test_atexit();
    printf("hello, world!\n");
}
