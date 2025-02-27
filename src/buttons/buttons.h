#ifndef BUTTONS_H
#define BUTTONS_H

#include "pico/stdlib.h"

#define BUTTON_A 5
#define BUTTON_B 6

// Funções públicas
void init_buttons(void);
bool is_button_a_pressed(void);
bool is_button_b_pressed(void);

#endif