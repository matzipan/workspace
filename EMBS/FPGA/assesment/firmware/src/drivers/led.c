#include "led.h"

unsigned int current_state = 0;

void led_set_value(unsigned int position, unsigned int value) { // 0 index position
	if(value == 0) {
		current_state &= ~(1<<position);
	} else {
		current_state |= 1<<position;
	}

    XGpio_WriteReg(XPAR_LEDS_8BIT_BASEADDR, 0, current_state);
}

unsigned int led_get_value(unsigned int position) { // 0 index position
    return (current_state >> position) & 1;
}

void led_clear_all() {
	current_state = 0;
    XGpio_WriteReg(XPAR_LEDS_8BIT_BASEADDR, 0, 0);
}
