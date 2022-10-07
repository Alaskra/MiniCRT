#pragma once

// entry.c
void print_int(unsigned i);

// malloc.c
#define NULL 0
int mini_crt_heap_init();
void* malloc(unsigned size);

// stdio.c
typedef struct FILE {
    int fd;
}FILE;
#define EOF (-1)
extern FILE FILE0;
extern FILE FILE1;
extern FILE FILE2;
extern FILE *stdin;
extern FILE *stdout;
extern FILE *stderr;

int mini_crt_io_init();
FILE* fopen(const char *filename, const char *mode);
int fread(void *buf, unsigned size, int count, FILE* stream);
int fwrite(const void *buf, unsigned size, int count, FILE* stream);
int fclose(FILE* fp);
int fseek(FILE* fp, int offset, int set);

// string.c
char *itoa(int n, char *str, int radix);
int strcmp(const char *src, const char *dst);
char *strcpy(char *dst, const char *src);
int strlen(const char *str);
