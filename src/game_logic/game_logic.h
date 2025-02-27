#include <stdbool.h>
#include <stdlib.h> // Para rand()

// Declarando as variáveis externas
extern int score;                // Pontuação
extern int life;                 // Vida
#define MAX_ASTEROIDS 5          // Número máximo de asteroides na tela
#define ASTEROID_SPAWN_RATE 10   // Probabilidade de gerar um asteroide
#define SPECIAL_SHOT_COOLDOWN 10 // Cooldown do tiro especial

// Variáveis globais
extern int ship_position;
extern int shot_position;
extern bool is_special_shot;
extern int asteroids[MAX_ASTEROIDS][2]; // [coluna, linha] de cada asteroide
extern int asteroid_count;

// Funções
void init_game(void);
void update_game(void);
void draw_game(void);
void spawn_asteroid(void);
void update_asteroids(void);
void draw_asteroids(void);
