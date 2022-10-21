#include "minicrt.h"

// modern system use .init_array instead of .ctors
// the default ld script have support, use .ctors is invalid
// https://maskray.me/blog/2021-11-07-init-ctors-init-array
void_func ctors_begin[1] __attribute__ ((section(".init_array"))) = {
    (void_func) -1
};

void run_hooks() {
    const void_func *list = ctors_begin;
    while ((long)*++list != -1) {
        (**list)();
    }
}

extern "C" void do_global_ctors() { run_hooks(); }
