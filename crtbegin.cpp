#include "minicrt.h"

ctor_func ctors_begin[1] __attribute__ ((section(".ctors"))) = {
    (ctor_func) -1
};

void run_hooks() {
    const ctor_func *list = ctors_begin;
    while ((long)*++list != -1) {
        (**list)();
    }
}
