#include "led.h"
#include "pico/stdlib.h"
#include <stdio.h>

/* Tempo de piscar: O tempo de piscar foi ajustado para 100 ms
para cada estado (ligado e desligado), totalizando 200 ms por
ciclo completo. Isso resulta em 5 ciclos por segundo (1000 ms / 200 ms = 5). */

#define TEMPO 100 // 100 ms para cada metade do ciclo (ligar/desligar)

void init_led(void)
{
	gpio_init(LED_RED_PIN);
	gpio_set_dir(LED_RED_PIN, GPIO_OUT);
}

void set_led_color()
{
	gpio_put(LED_RED_PIN, true);
	sleep_ms(TEMPO);
	gpio_put(LED_RED_PIN, false);
	sleep_ms(TEMPO);
}