#include "lpc17xx_pinsel.h"
#include "lpc_types.h"
#include "lpc17xx_gpio.h"
#include "limits.h"
#include "lpc17xx_rit.h"

#define TIME_INTERVAL   1000
#define LED_LENGTH 4
const int ledPinnum[] = { 18, 20, 21, 23 };

int number = 0;

void gpio_init() {
	int i=0;
	PINSEL_CFG_Type 	PinCfg;

	PinCfg.Funcnum = 0;
	PinCfg.OpenDrain = 0;
	PinCfg.Pinmode = 0;
	
	PinCfg.Portnum = 1;

	for(; i<LED_LENGTH; i++) {
		PinCfg.Pinnum = ledPinnum[i];
		PINSEL_ConfigPin(&PinCfg);

		GPIO_SetDir(1, 1<<ledPinnum[i], 1);  
	}
}

void RIT_IRQHandler(void) {
	RIT_GetIntStatus(LPC_RIT); //call this to clear interrupt flag

	display_number(number);
	number++;
}

void rit_init() {
	RIT_Init(LPC_RIT);

	RIT_TimerConfig(LPC_RIT,TIME_INTERVAL);

	NVIC_EnableIRQ(RIT_IRQn);
}

void led_on(int id) {
	GPIO_SetValue(1, 1<<ledPinnum[id]);
}

void led_off(int id) {
	GPIO_ClearValue(1, 1<<ledPinnum[id]);
}

void delay() {
	volatile int i=0;
	for(;i<10000000;i++);
}

void display_number(int x) {
	int i=1;
	int p=0;
	for(; i<16; i<<=1) {		
		if(x&i) {
			led_on(p);
		} else {
			led_off(p);
		}

		p++;
	}
}

void main() { 
	gpio_init();
	rit_init();

	while(1);
}



