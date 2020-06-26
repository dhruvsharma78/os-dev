#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/* Check if we're compiling for the correct OS.
 * I don't think this part is really needed,
 * but just a safety check to prevent compiling
 * incorrectly. Saves time if you compile incorrectly
 * by mistake
*/

#if defined(__linux__)
#error "Use a cross compiler!!"
#endif

#if !defined(__i386__)
#error "Use an ix86-elf compiler!!"
#endif

/* Hardware VGA colors */
enum vga_color {
    VGA_COLOR_BLACK = 0,
    VGA_COLOR_BLUE,
    VGA_COLOR_GREEN,
    VGA_COLOR_CYAN,
    VGA_COLOR_RED,
    VGA_COLOR_MAGENTA,
    VGA_COLOR_BROWN,
    VGA_COLOR_LIGHT_GREY,
    VGA_COLOR_DARK_GREY,
    VGA_COLOR_LIGHT_BLUE,
    VGA_COLOR_LIGHT_GREEN,
    VGA_COLOR_LIGHT_CYAN,
    VGA_COLOR_LIGHT_RED,
    VGA_COLOR_LIGHT_MAGENTA,
    VGA_COLOR_LIGHT_BROWN,
    VGA_COLOR_WHITE,
};

static inline uint8_t vga_entry_color(enum vga_color fg, enum vga_color bg, bool blink){
    /* | Blink | Background | Foreground |
     * |   7   |     6-4    |     3-0    |
    */
    return (fg | bg << 4) | (blink << 7);
}

static inline uint16_t vga_entry(unsigned char ch, uint8_t color){
    /* | Color | Char |
     * | 15-8  | 7-0  |
    */
    return (uint16_t) ch | (uint16_t) color << 8;
} 

size_t strlen(const char* str){
    size_t len = 0;
    while(str[len])
        ++len;
    return len;
}

static const size_t VGA_WIDTH  = 80;
static const size_t VGA_HEIGHT = 25;

size_t    terminal_row;
size_t    terminal_col;
uint8_t   terminal_color;
uint16_t* terminal_buffer;

void terminal_init(void){
    terminal_row = 0;
    terminal_col = 0;
    terminal_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK, 0);
    terminal_buffer = (uint16_t*) 0xB8000;
    
    /* Load up terminal with the background color */
    size_t y;
    for(y=0; y < VGA_HEIGHT; ++y){
        for(size_t x=0; x < VGA_WIDTH; ++x){
            terminal_buffer[(y*VGA_WIDTH) + x] = vga_entry(' ', terminal_color);
        }
    }
} 

void terminal_setcolor(uint8_t color){
    terminal_color = color;
}

void terminal_putentry(char ch, uint8_t color, size_t x, size_t y){
    terminal_buffer[(y*VGA_WIDTH) + x] = vga_entry(ch, color);
}

void terminal_putchar(char ch){
    terminal_putentry(ch, terminal_color, terminal_col, terminal_row);
    /* If at the EOL, start rewriting */
    // TODO: line breaks
    if(++terminal_col == VGA_WIDTH){
        terminal_col = 0;
        if(++terminal_row == VGA_HEIGHT){
            terminal_row = 0;
        }
    }
}

void terminal_writestr(const char* str){
    size_t i;
    size_t size;
    size = strlen(str);
    for(i=0; i<size; ++i){
        terminal_putchar(str[i]);
    }
}

void kmain(void){
    terminal_init();
    terminal_writestr("Kernel Activated....\n");
}
