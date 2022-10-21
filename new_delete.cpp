#include "minicrt.h"

void *operator new(unsigned long size) {
    return malloc(size);
}

void *operator new[](unsigned long size) {
    return malloc(size);
}

void operator delete(void *p) {
    return free(p);
}

void operator delete[](void *p) {
    return free(p);
}

// since c++14, delete is convert to  `operator delete(void*, unsigned long)'
void operator delete(void *p, unsigned long x) {
    return free(p);
}
