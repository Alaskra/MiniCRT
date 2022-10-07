#include "minicrt.h"

FILE FILE0 = {0};
FILE FILE1 = {1};
FILE FILE2 = {2};
FILE *stdin = &FILE0;
FILE *stdout = &FILE1;
FILE *stderr = &FILE2;

int mini_crt_io_init() {
    return 1;
}

static int open(const char *pathname, int flags, int mode) {
    // sys_open's syscall number is 2
    // gcc extended inline asm:
    // "a" is rax, "D" is rdi, "S" is rsi, "d" is rdx
    asm("syscall \n\t"
        ::"a"(2), "D"(pathname), "S"(flags), "d"(mode));
}

static int read(unsigned fd, void *buf, unsigned size) {
    // sys_read's syscall number is 0
    asm("syscall \n\t"
        ::"a"(0), "D"(fd), "S"(buf), "d"(size));
}


static int write(unsigned fd, const void *buf, unsigned  size) {
    // sys_read's syscall number is 1
    asm ("syscall \n\t"
        ::"a"(1), "D"(fd), "S"(buf), "d"(size));
}

static int close(unsigned fd) {
    // sys_read's syscall number is 3
    asm("syscall \n\t"
        ::"a"(3), "D"(fd));
}

static int seek(unsigned fd, int offset, int mode) {
    // sys_lseek's syscall number is 8
    asm("syscall \n\t"
        ::"a"(8), "D"(fd), "S"(offset), "d"(mode));
}

FILE* fopen(const char *filename, const char *mode) {
/* FILE fopen(const char *filename, const char *mode) { */
    int fd = -1;
    int flags = 0;
    int access = 0700;  // octal value
    #define O_RDONLY 00
    #define O_WRONLY 01
    #define O_RDWR   02
    #define O_CREAT  0100
    #define O_TRUNC  01000
    #define O_APPEND 02000
    if(strcmp(mode, "w") == 0)  // fix latter: need include string.h?
        flags |= O_WRONLY | O_CREAT | O_TRUNC;
    if(strcmp(mode, "w+") == 0)
        flags |= O_RDWR | O_CREAT | O_TRUNC;
    if(strcmp(mode, "r") == 0)
        flags |= O_RDONLY;
    if(strcmp(mode, "r+") == 0)
        flags |= O_RDONLY | O_CREAT;
    fd = open(filename, flags, access);
    FILE* ret = (FILE*)malloc(sizeof(FILE));
    ret->fd = fd;
    /* FILE ret; */
    /* ret.fd = fd; */
    return ret;
}

int fread(void *buf, unsigned size, int count, FILE* stream) {
    return read(stream->fd, buf, size*count);
}

int fwrite(const void *buf, unsigned size, int count, FILE* stream) {
    return write(stream->fd, buf, size*count);
}

int fclose(FILE* fp) {
    return close(fp->fd);
}

int fseek(FILE* fp, int offset, int set) {
    return seek(fp->fd, offset, set);
}
