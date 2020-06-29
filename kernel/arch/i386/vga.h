#ifndef ARCH_I386_VGA_H
#define ARCH_I386_VGA_H

#include <stdint.h>

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
 
#endif
