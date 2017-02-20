#include "xil_types.h"
#include "xparameters.h"

#ifndef VGA_H_
#define VGA_H_

// Set these values to match those chosen in XPS
#define VGA_WIDTH          800
#define VGA_HEIGHT         600
#define VGA_BITS_PER_PIXEL 8
#define VGA_DATATYPE u8
///////////////////////////////////////////////////


#define VGA_BLACK   0b00000000
#define VGA_WHITE   0b00000111
#define VGA_RED     0b00000100
#define VGA_GREEN   0b00000010
#define VGA_BLUE    0b00000001
#define VGA_CYAN    0b00000011
#define VGA_YELLOW  0b00000110
#define VGA_MAGENTA 0b00000101

#define VGA_FILL_SOLID 0
#define VGA_FILL_CHEQUERS 2


void vga_init();

void vga_enable_output();
void vga_disable_output();

void vga_draw_rect(int x_start, int y_start, int width, int height, u8 colour, u8 type);
void vga_draw_screen_border();

void vga_clear_screen();

void inline vga_set_pixel(int x, int y, u8 color);

#endif
