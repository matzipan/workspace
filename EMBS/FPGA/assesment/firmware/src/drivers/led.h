#include "xgpio_l.h"
#include "xparameters.h"

#ifndef LED_H_
#define LED_H_

void led_set_value(unsigned int position, unsigned int value);

unsigned int led_get_value(unsigned int position);

void led_clear_all();

#endif
