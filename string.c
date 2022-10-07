#include "minicrt.h"

char *itoa(int n, char *str, int base) {
    char *digit = "0123456789abcdefghijklmnopqrstuvwxyz";
    int idx = 0;
    int sign = 0;
    if(n == 0) {
        str[0] = '0';
        str[1] = 0;
        return str;
    } else if(n < 0) {
        str[0] = '-';
        sign = 1;
        idx++;
    }
    while(n != 0) {
        str[idx++] = digit[n%base];
        n /= base;
    }
    str[idx--] = 0;

    // reverse
    while(sign < idx) {
        int tmp = str[idx];
        str[idx] = str[sign];
        str[sign] = tmp;
        sign++;
        idx--;
    }
    return str;
}

int strcmp(const char *src, const char *dst) {
    int idx = 0;
    while(src[idx]!=0 && dst[idx]!=0) {
        if(src[idx] > dst[idx])
            return 1;
        else if(src[idx] < dst[idx])
            return -1;
        else
            idx++;
    }
    if(src[idx]==0 && dst[idx]==0)
        return 0;
    else if(src[idx] == 0)
        return -1;
    else
        return 1;
}

char *strcpy(char *dst, const char *src) {
    int idx = 0;
    while(src[idx] != 0) {
        dst[idx] = src[idx];
        idx++;
    }
    dst[idx] = src[idx];
}

int strlen(const char *str) {
    int idx = 0;
    while(str[idx] != 0)
        idx++;
    return idx;
}
