#include "minicrt.h"

int fputc(char c, FILE *stream) {
    return fwrite(&c, 1, 1, stream);
}

int fputs(const char *str, FILE *stream) {
    return fwrite(str, 1, strlen(str), stream);
}

static int vprintf(FILE *stream, const char *format, va_list arglist) {
    int translating = 0;
    int ret = 0;
    for(const char *p = format; *p != 0; p++) {
        if(translating) {
            switch(*p) {
                case 's':
                    char *str = va_arg(arglist, char*);
                    if(fputs(str, stream) < 0)
                        return -1;
                    ret += strlen(str);
                    break;
                case 'd':
                    char buf[20];
                    int a = va_arg(arglist, int);
                    itoa(a, buf, 10);
                    if(fputs(buf, stream) < 0)
                        return -1;
                    ret += strlen(buf);
                    break;
                default:
                    if(fputc(*p, stream) < 0)
                        return -1;
                    ret++;
            }
            translating = 0;
        } else {
            if(*p == '%') {
                translating = 1;
            } else {
                if(fputc(*p, stream) < 0)
                    return -1;
                ret++;
            }
        }
    }
    return ret;
}

int printf(const char *format, ...) {
    va_list arglist;
    va_start(arglist, format);
    return vprintf(stdout, format, arglist);
}

int fprintf(FILE *stream, const char *format, ...) {
    va_list arglist;
    va_start(arglist, format);
    return vprintf(stream, format, arglist);
}
