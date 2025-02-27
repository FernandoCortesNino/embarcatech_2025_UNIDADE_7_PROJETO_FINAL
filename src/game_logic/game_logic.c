#include <stdio.h>
#include <stdlib.h>
#include "game_logic.h"
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "ws2812.pio.h"

#include "../buttons/buttons.h"
#include "../matriz/matriz.h"
#include "hardware/i2c.h"
#include "../inc/ssd1306.h"     // Inclui o cabeçalho do SSD1306
#include "../display/display.h" // Inclui o cabeçalho do display
#include <time.h>               // Para time()

// Declaração da variável externa led_buffer
extern uint32_t led_buffer[NUM_PIXELS];

// Variáveis globais específicas do game_logic.c
int score = 0;                   // Pontuação do jogador
int life = 3;                    // Vida do jogador
bool is_special_shot = false;    // Indica se o tiro é especial
int asteroids[MAX_ASTEROIDS][2]; // [coluna, linha] de cada asteroide
int asteroid_count = 0;          // Quantidade de asteroides ativos

// Variáveis auxiliares para evitar flicker no display
int last_score = -1; // Valor anterior da pontuação
int last_life = -1;  // Valor anterior da vida

// Variáveis para controlar o tempo de geração e queda de asteroides
uint32_t last_asteroid_time = 0;
uint32_t last_asteroid_fall_time = 0;

// Declaração da variável do display
extern ssd1306_t ssd;

// Inicializa o jogo
void init_game(void)
{
    ship_position = 2;
    shot_position = -1;
    is_special_shot = false;
    asteroid_count = 0;
    score = 0;                            // Reinicia a pontuação
    life = 3;                             // Reinicia a vida
    last_asteroid_time = time(NULL);      // Inicializa o tempo de geração de asteroides
    last_asteroid_fall_time = time(NULL); // Inicializa o tempo de queda de asteroides
    init_led_matrix();                    // Limpa a matriz
}

// Atualiza a lógica do jogo
void update_game(void)
{
    // Verifica se o botão A (especial) foi pressionado
    if (is_button_a_pressed() && shot_position == -1)
    {
        shot_position = MATRIX_HEIGHT - 1;  // Inicia o tiro na base da matriz
        is_special_shot = true;             // Tiro especial
        printf("Tiro especial ativado.\n"); // Depuração
    }

    // Verifica se o botão B (normal) foi pressionado
    if (is_button_b_pressed() && shot_position == -1)
    {
        shot_position = MATRIX_HEIGHT - 1; // Inicia o tiro na base da matriz
        is_special_shot = false;           // Tiro normal
        printf("Tiro normal ativado.\n");  // Depuração
    }

    // Atualiza a posição do tiro
    if (shot_position != -1)
    {
        shot_position--; // Move o tiro para cima
        if (shot_position < 0)
        {
            shot_position = -1; // Tiro saiu da matriz
            if (is_special_shot)
            {
                // Destrói todos os asteroides (limpa a matriz)
                init_led_matrix();
                asteroid_count = 0;                                      // Remove todos os asteroides
                printf("Tiro especial destruiu todos os asteroides.\n"); // Depuração
            }
        }
    }

    // Gera novos asteroides aleatoriamente com intervalo de pelo menos 0.3 segundos
    uint32_t current_time = time(NULL);
    if (current_time - last_asteroid_time >= 0.3) // Intervalo de 0.3 segundos
    {
        spawn_asteroid();
        last_asteroid_time = current_time;  // Atualiza o tempo da última geração
        printf("Novo asteroide gerado.\n"); // Depuração
    }

    // Atualiza a posição dos asteroides
    update_asteroids();

    // Verifica colisões com os asteroides
    for (int i = 0; i < asteroid_count; i++)
    {
        if (asteroids[i][0] == ship_position && asteroids[i][1] == 0)
        {
            // Colidiu com a nave, perde uma vida
            life--;
            if (life <= 0)
            {
                // Game Over
                init_game();                                // Reinicia o jogo
                printf("Game Over! Reiniciando o jogo.\n"); // Depuração
            }
        }
    }

    // Atualiza o display apenas se a pontuação ou a vida mudaram
    if (score != last_score || life != last_life)
    {
        draw_score(&ssd, score);
        draw_life(&ssd, life);
        last_score = score; // Atualiza o valor anterior da pontuação
        last_life = life;   // Atualiza o valor anterior da vida
    }
}

// Desenha o estado atual do jogo
void draw_game(void)
{
    // Limpa o buffer de LEDs
    for (int i = 0; i < NUM_PIXELS; i++)
    {
        led_buffer[i] = 0; // Define todos os pixels como desligados
    }

    // Desenha a nave
    put_pixel_at(ship_position, 0, urgb_u32(0, 26, 0));        // Nave verde
    printf("Desenhando nave na posição: %d\n", ship_position); // Depuração

    // Desenha o tiro
    if (shot_position != -1)
    {
        if (is_special_shot)
        {
            put_pixel_at(ship_position, shot_position, urgb_u32(26, 26, 0)); // Tiro amarelo (especial)
        }
        else
        {
            put_pixel_at(ship_position, shot_position, urgb_u32(26, 0, 0)); // Tiro vermelho (normal)
        }
        printf("Desenhando tiro na posição: %d\n", shot_position); // Depuração
    }

    // Desenha os asteroides
    draw_asteroids();

    // Atualiza a matriz de LEDs
    set_leds_from_buffer();
}

// Gera um novo asteroide
void spawn_asteroid(void)
{
    if (asteroid_count < MAX_ASTEROIDS)
    {
        int col = rand() % MATRIX_WIDTH;                  // Coluna aleatória (0 a 4)
        asteroids[asteroid_count][0] = col;               // Coluna
        asteroids[asteroid_count][1] = MATRIX_HEIGHT - 1; // Linha (topo da matriz, y = 4)
        asteroid_count++;
    }
}

// Atualiza a posição dos asteroides
void update_asteroids(void)
{
    uint32_t current_time = time(NULL);

    // Verifica se passou tempo suficiente para mover os asteroides
    if (current_time - last_asteroid_fall_time >= 1) // Ajuste o valor para controlar a velocidade
    {
        for (int i = 0; i < asteroid_count; i++)
        {
            asteroids[i][1]--; // Move o asteroide para baixo

            // Remove o asteroide quando ele sai da matriz
            if (asteroids[i][1] < 0)
            {
                for (int j = i; j < asteroid_count - 1; j++)
                {
                    asteroids[j][0] = asteroids[j + 1][0];
                    asteroids[j][1] = asteroids[j + 1][1];
                }
                asteroid_count--;
                i--; // Ajusta o índice após remover um asteroide
            }
        }

        last_asteroid_fall_time = current_time; // Atualiza o tempo da última queda
    }
}

// Desenha os asteroides na matriz
void draw_asteroids(void)
{
    for (int i = 0; i < asteroid_count; i++)
    {
        int col = asteroids[i][0];
        int row = asteroids[i][1];
        if (row >= 0 && row < MATRIX_HEIGHT) // Verifica se o asteroide está dentro da matriz
        {
            put_pixel_at(col, row, urgb_u32(0, 0, 26)); // Asteroide azul
        }
    }
}