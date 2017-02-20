#include "vga.h"

VGA_DATATYPE vga_frame_buffer[VGA_HEIGHT][VGA_WIDTH];

void vga_init() {
    // Set VGA core frame buffer location
    *((volatile unsigned int *) XPAR_EMBS_VGA_0_BASEADDR) = vga_frame_buffer;
}

void vga_enable_output() {
    *((volatile unsigned int *) XPAR_EMBS_VGA_0_BASEADDR + 1) = 1;
}

void vga_disable_output() {
    *((volatile unsigned int *) XPAR_EMBS_VGA_0_BASEADDR + 1) = 0;
}


// Draws a rectangle of solid colour on the screen
void vga_draw_rect(int x_start, int y_start, int width, int height, u8 colour, u8 type) {
    int x, y;

    if(type == VGA_FILL_SOLID) {
    	for (y = y_start; y < y_start + height; y++) {
			for (x = x_start; x < x_start + width; x++) {
				vga_set_pixel(x, y, colour);
			}
		}
    }
    if(type == VGA_FILL_CHEQUERS) {
    	u8 odd = 0;
		for (y = y_start; y < y_start + height; y++) {
			for (x = x_start; x < x_start + width; x++) {
				vga_set_pixel(x, y, (odd ? VGA_BLACK : colour));
				odd = !odd;
			}
			odd = !odd;
		}
    }
}

void vga_clear_screen() {
	vga_draw_rect(0,0, VGA_WIDTH, VGA_HEIGHT, VGA_BLACK, VGA_FILL_SOLID);
}

// Draws a white border around the screen
void vga_draw_screen_border() {
    int i;
    for (i = 0; i < VGA_HEIGHT; i++) {
        vga_set_pixel(0, i, VGA_WHITE);
        vga_set_pixel(VGA_WIDTH,i, VGA_WHITE);
    }
    for (i = 0; i < VGA_WIDTH; i++) {
    	vga_set_pixel(i,0, VGA_WHITE);
    	vga_set_pixel(i,VGA_HEIGHT, VGA_WHITE);
    }
}

void inline vga_set_pixel(int x, int y, u8 colour) {
    // confusingly, this matrix is transposed!
	 vga_frame_buffer[y][x] = colour;
}
