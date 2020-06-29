#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include <kernel/tty.h>

#include "vga.h"

static const size_t VGA_WIDTH  = 80;
static const size_t VGA_HEIGHT = 25;

#define TERM_INDEX(x, y) y*VGA_WIDTH+x

static uint16_t* const VGA_MEMORY = (uint16_t*) 0xb8000;

static size_t    terminal_row;
static size_t    terminal_col;
static uint8_t   terminal_color;
static uint16_t* terminal_buffer;

void terminal_init(void) {
    terminal_row = 0;
    terminal_col = 0;
    terminal_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK, 0);
    terminal_buffer = VGA_MEMORY;
    size_t x, y;
    for(y=0; y < VGA_HEIGHT; ++y) {
        for(x=0; x < VGA_WIDTH; ++x) {
            terminal_buffer[TERM_INDEX(x,y)] = vga_entry(' ', terminal_color);
        }
    }
}

void terminal_setcolor(uint8_t color) {
    terminal_color = color;
}

void terminal_putentry(unsigned char ch, uint8_t color, size_t x, size_t y) {
    terminal_buffer[TERM_INDEX(x,y)] = vga_entry(ch, color);
}

void terminal_putchar(char ch) {
    switch(ch){
        case '\n':
            terminal_col = 0;
            ++terminal_row;
            break;
        default:
            terminal_putentry((unsigned char) ch, terminal_color, terminal_col, terminal_row);
            break;
    }
    if(++terminal_col == VGA_WIDTH){
        terminal_col = 0;
        ++terminal_row;
    }
}

void terminal_write(const char* str) {
    size_t len = strlen(str);
    size_t i;
    for(i=0; i<len; ++i){
        terminal_putchar(str[i]);
    }
}
