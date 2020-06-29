#include <stdio.h>

#if defined(__is_libk)
#include <kernel/tty.h>
#endif

int putchar(int ci) {
#if defined(__is_libk)
    char ch = (char) ci;
    terminal_putchar(ch);
#else
    // TODO: Syscall implementation
#endif
    return ci;
}
