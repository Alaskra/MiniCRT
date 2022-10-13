#pragma once

#ifdef __cplusplus
extern "C" {
#endif

// entry.c
void print_int(unsigned i);

// malloc.c
#define NULL (0)
int mini_crt_heap_init();
void* malloc(unsigned size);
void free(void *ptr);
static long brk(void* end_data_segment);

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

// printf.c
// only valid in 32 bit system
// according to x86 64 bit calling convention, function parameters are stored in register first
// the following code are invalid
// #define va_list char*
// #define va_start(ap,arg) (ap=(va_list)&arg+sizeof(arg))
// #define va_arg(ap,t) (*(t*)((ap+=sizeof(t))-sizeof(t)))
// #define va_end(ap) (ap=(va_list)0)

// use gcc builtin function
#define va_list __builtin_va_list
#define va_arg(ap, type) __builtin_va_arg(ap, type)
#define va_start(v, l) __builtin_va_start(v, l)
#define va_end(v) __builtin_va_end(v)
int fputc(char c, FILE *stream);
int fputs(const char *str, FILE *stream);
int printf(const char *format, ...);
int fprintf(FILE *stream, const char *format, ...);
static int vprintf(FILE *stream, const char *format, va_list arglist);

// internal
void do_global_ctors();
void mini_crt_call_exit_routine();

// atexit
typedef void (*atexit_func_t) (void);
int atexit(atexit_func_t func);

#ifdef __cplusplus
}
#endif
