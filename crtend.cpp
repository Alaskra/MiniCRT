#include "minicrt.h"

// same as comment in crtbegin.cpp
void_func ctors_end[1] __attribute__ ((section(".init_array"))) = {
    (void_func) -1
};
