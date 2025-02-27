#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "ws2812.pio.h"

#include "joystick/joystick.h"
#include "buttons/buttons.h"
#include "matriz/matriz.h"
#include "game_logic/game_logic.h"
#include "hardware/i2c.h"
#include "inc/ssd1306.h"
#include "inc/font.h"
#include "display/display.h"

PIO pio = pio0;
int sm = 0;
uint offset;

// Declaração das variáveis globais
int ship_position = 2;  // Posição inicial da nave (centro da matriz)
int shot_position = -1; // Posição do tiro (-1 significa que não há tiro ativo)

// Declaração da variável do display
ssd1306_t ssd;

int main()
{
  stdio_init_all();

  // Inicializa o PIO para os LEDs WS2812
  offset = pio_add_program(pio, &ws2812_program);
  ws2812_program_init(pio, sm, offset, WS2812_PIN, 800000, IS_RGBW);

  // Inicializa o display
  init_display(&ssd);

  // Inicializa os módulos
  init_joystick();
  init_buttons();
  init_led_matrix();

  // Inicializa o jogo
  init_game();

  while (true)
  {
    // Leitura do joystick (movimento para esquerda e direita)
    int y_value = read_joystick_y();
    printf("Joystick Y: %d\n", y_value); // Depuração

    // Ajuste para corrigir a inversão do joystick
    if (y_value > 3000 && ship_position > 0) // Movimento para a esquerda
    {
      ship_position--;                                                      // Move a nave para a esquerda
      printf("Movendo para a esquerda. Nova posição: %d\n", ship_position); // Depuração
    }
    else if (y_value < 1000 && ship_position < MATRIX_WIDTH - 1) // Movimento para a direita
    {
      ship_position++;                                                     // Move a nave para a direita
      printf("Movendo para a direita. Nova posição: %d\n", ship_position); // Depuração
    }

    // Atualiza a lógica do jogo
    update_game();

    // Desenha o estado atual do jogo
    draw_game();

    sleep_ms(100); // Atraso para controle de FPS
  }
  return 0;
}