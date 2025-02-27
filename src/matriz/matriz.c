#include "matriz.h"
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "ws2812.pio.h"

// Utilizamos a variável externa definida em main.c para o PIO e a state machine
extern PIO pio;
extern int sm;

// Buffer para armazenar o estado de cada LED na matriz
uint32_t led_buffer[NUM_PIXELS] = {0};

uint32_t urgb_u32(uint8_t r, uint8_t g, uint8_t b)
{
    return ((uint32_t)(r) << 8) | ((uint32_t)(g) << 16) | (uint32_t)(b);
}

void put_pixel(uint32_t pixel_grb)
{
    pio_sm_put_blocking(pio0, sm, pixel_grb << 8u); // Ajuste aqui para garantir que o valor seja enviado à state machine
}

void put_pixel_at(int x, int y, uint32_t pixel_grb)
{
    int index = y * MATRIX_WIDTH + x;
    if (index >= 0 && index < NUM_PIXELS) // Verifica se o índice está dentro dos limites
    {
        led_buffer[index] = pixel_grb;
    }
}

void set_leds_from_buffer()
{
    for (int i = 0; i < NUM_PIXELS; i++)
    {
        put_pixel(led_buffer[i]);
    }
}

// Inicializa a matriz de LEDs (ex.: limpa o buffer)
void init_led_matrix(void)
{
    for (int i = 0; i < NUM_PIXELS; i++)
    {
        led_buffer[i] = 0;
    }
    set_leds_from_buffer(); // Atualiza a matriz de LEDs
}

// Atualiza a posição da nave (sprite 1x1) na linha 0 (base da matriz)
void update_ship_position(int position)
{
    // Desenha a nave (1x1) na linha 0
    put_pixel_at(position, 0, urgb_u32(0, 26, 0)); // Cor verde para a nave
    set_leds_from_buffer();                        // Atualiza a matriz de LEDs
}