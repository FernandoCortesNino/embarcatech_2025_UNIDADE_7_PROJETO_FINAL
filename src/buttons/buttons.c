#include "buttons.h"
#include "pico/stdlib.h"

// Variáveis globais para debounce
static volatile uint32_t last_time_a = 0;
static volatile uint32_t last_time_b = 0;
static volatile bool button_a_pressed = false;
static volatile bool button_b_pressed = false;

// Função de interrupção com debounce
void gpio_irq_handler(uint gpio, uint32_t events)
{
    uint32_t current_time = to_us_since_boot(get_absolute_time());

    if (gpio == BUTTON_A && (current_time - last_time_a > 200000))
    {
        last_time_a = current_time;
        button_a_pressed = true;
    }
    else if (gpio == BUTTON_B && (current_time - last_time_b > 200000))
    {
        last_time_b = current_time;
        button_b_pressed = true;
    }
}

void init_buttons()
{
    gpio_init(BUTTON_A);
    gpio_init(BUTTON_B);
    gpio_set_dir(BUTTON_A, GPIO_IN);
    gpio_set_dir(BUTTON_B, GPIO_IN);
    gpio_pull_up(BUTTON_A);
    gpio_pull_up(BUTTON_B);
    gpio_set_irq_enabled_with_callback(BUTTON_A, GPIO_IRQ_EDGE_FALL, true, &gpio_irq_handler);
    gpio_set_irq_enabled_with_callback(BUTTON_B, GPIO_IRQ_EDGE_FALL, true, &gpio_irq_handler);
}

bool is_button_a_pressed()
{
    if (button_a_pressed)
    {
        button_a_pressed = false;
        return true;
    }
    return false;
}

bool is_button_b_pressed()
{
    if (button_b_pressed)
    {
        button_b_pressed = false;
        return true;
    }
    return false;
}