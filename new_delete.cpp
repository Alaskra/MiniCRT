#include "minicrt.h"

void *operator new(unsigned int size) {
    return malloc(size);
}

void *operator new[](unsigned int size) {
    return malloc(size);
}

void operator delete(void *p) {
    return free(p);
}

void operator delete[](void *p) {
    return free(p);
}
