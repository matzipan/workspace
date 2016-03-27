#include "stdio.h"
#include "xgpio_l.h"
#include "xparameters.h"

int main() {
	int pressed = 0;

	while(1) {
		int new_value = 0;

		pressed |= (XGpio_ReadReg(XPAR_BUTTONS_4BIT_BASEADDR, 0)) & 0xE;

		// north button to led 2
		new_value |= ((pressed >> 1) & 0x1) << 2;
		// east button to led 0
		new_value |= ((pressed >> 2) & 0x1) << 0;
		// west button to led 1
		new_value |= ((pressed >> 3) & 0x1) << 1;

		// switch at position 0 to led 4
		new_value |= ((XGpio_ReadReg(XPAR_DIP_SWITCHES_4BIT_BASEADDR, 0) >> 0) & 0x1) << 4;
		// switch at position 1 to led 5
		new_value |= ((XGpio_ReadReg(XPAR_DIP_SWITCHES_4BIT_BASEADDR, 0) >> 1) & 0x1) << 5;
		// switch at position 2 to led 6
		new_value |= ((XGpio_ReadReg(XPAR_DIP_SWITCHES_4BIT_BASEADDR, 0) >> 2) & 0x1) << 6;
		// switch at position 3 to led 7
		new_value |= ((XGpio_ReadReg(XPAR_DIP_SWITCHES_4BIT_BASEADDR, 0) >> 3) & 0x1) << 7;

		XGpio_WriteReg(XPAR_LEDS_8BIT_BASEADDR, 0, new_value);
	}

    return 0;
}
