#include <stdio.h>

#include <kernel/tty.h>

void kmain(void) {
    terminal_init();
    printf("Welcome to the coffeeOS kernel...\nWaiting...");
}
