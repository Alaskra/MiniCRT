#pragma once

#ifdef __cplusplus
extern "C" {
#endif

// entry.c
void mini_crt_entry();

// malloc.c
#define NULL (0)
int mini_crt_heap_init();
void* malloc(unsigned long size);
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
typedef void (*cxa_func_t)(void*);
typedef void (*atexit_func_t) (void);
int atexit(atexit_func_t func);
int __cxa_atexit(cxa_func_t func, void *arg, void *unused);

typedef void (*void_func)(void);

#ifdef __cplusplus

extern void * __dso_handle;
} // end of extern "C"

// iostream and string
namespace std{
    class ofstream {
    protected:
        FILE* fp;
        ofstream(const ofstream&);
    public:
        enum openmode{in =1, out=2, binary = 4, trunc = 8};

        ofstream();
        explicit ofstream(const char* filename, ofstream::openmode md = ofstream::out);
        ~ofstream();
        ofstream& operator<<(char c);
        ofstream& operator<<(int n);
        ofstream& operator<<(const char* str);
        ofstream& operator<<(ofstream& (*)(ofstream&));
        void open(const char* filename, ofstream::openmode md = ofstream::out);
        void close();

        ofstream& write(const char* buf, unsigned size);
    };

    inline ofstream& endl(ofstream& o) {
        return o<<'\n';
    }

    class stdout_stream : public ofstream {
    public:
        stdout_stream();
    };

    extern stdout_stream cout;

    class string {
        unsigned len;
        char* pbuf;

    public:
        explicit string(const char* str);
        string(const string&);
        ~string();

        string& operator = (const string&);
        string& operator = (const char* s);
        // https://www.learncpp.com/cpp-tutorial/overloading-the-subscript-operator/
        // The non-const version will be used with non-const objects,
        // and the const version with const-objects.
        const char& operator[] (unsigned idx) const;
        char& operator[] (unsigned idx);

        const char* c_str() const;
        unsigned length() const;
        unsigned size() const;
    };
    ofstream& operator<<(ofstream& o, const string& s);
}
#endif
