#ifndef _LED_H
#define _LED_H

#include <stdbool.h>

#define LED_RED_PIN 13
#define LED_GREEN_PIN 11
#define LED_BLUE_PIN 12

void init_led(void);
void set_led_color();

#endif