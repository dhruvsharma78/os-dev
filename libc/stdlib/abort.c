#include <stdio.h>
#include <stdlib.h>

__attribute__((__noreturn__)) void abort(void) {
#if defined(__is_libk)
    // TODO: Make a proper kernel panic
    printf("kernel: panic, aborting...\n");
#else
    // TODO: Make properly
    printf("abort..");
#endif
    // Loop forever
    while(1);
    __builtin_unreachable();
}
