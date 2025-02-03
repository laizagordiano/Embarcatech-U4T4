#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "hardware/adc.h"
#include "pico/bootrom.h"

//arquivo .pio
#include "pio_matrix.pio.h"

// Definição dos pinos
#define LED_PIN_GREEN 11
#define LED_PIN_BLUE 12
#define LED_PIN_RED 13
#define LED_PIN 7
#define NUM_PIXELS 25
#define BOTAO_A_PIN 5
#define BOTAO_B_PIN 6

// Variáveis Globais
PIO pio;
uint sm;
int id = 0;
uint last_time = 0;

// Função para a definição da cor na matriz
uint matrix_rgb(double r, double g, double b) {
    unsigned char R, G, B;
    R = r * 255;
    G = g * 255;
    B = b * 255;
    return (G << 24) | (R << 16) | (B << 8);
}

// Sprites dos números
double numero_1[25] =   
   {0, 0, 1, 0, 0,
    0, 0, 1, 0, 0,
    0, 0, 1, 0, 0,
    0, 1, 1, 0, 0,
    0, 0, 1, 0, 0,};

double numero_2[25] =    
   {0, 1, 1, 1, 0,
    0, 1, 0, 0, 0,
    0, 0, 1, 0, 0,
    0, 0, 0, 1, 0,
    0, 1, 1, 1, 0,};

double numero_3[25] = 
   {0, 1, 1, 1, 0,
    0, 0, 0, 1, 0,
    0, 1, 1, 1, 0,
    0, 0, 0, 1, 0,
    0, 1, 1, 1, 0,};  

double numero_4[25] =    
   {0, 1, 0, 0, 0,
    0, 0, 0, 1, 0,
    0, 1, 1, 1, 0,
    0, 1, 0, 1, 0,
    0, 1, 0, 1, 0,};

double numero_5[25] =    
   {0, 1, 1, 1, 0,
    0, 0, 0, 1, 0,
    0, 1, 1, 1, 0,
    0, 1, 0, 0, 0,
    0, 1, 1, 1, 0,};

double numero_6[25] =    
   {0, 1, 1, 1, 0,
    0, 1, 0, 1, 0,
    0, 1, 1, 1, 0,
    0, 1, 0, 0, 0,
    0, 1, 1, 1, 0,};

double numero_7[25] =    
   {0, 0, 0, 1, 0,
    0, 1, 0, 0, 0,
    0, 0, 1, 0, 0,
    0, 0, 0, 1, 0,
    0, 1, 1, 1, 0,};

double numero_8[25] =    
   {0, 1, 1, 1, 0,
    0, 1, 0, 1, 0,
    0, 1, 1, 1, 0,
    0, 1, 0, 1, 0,
    0, 1, 1, 1, 0,};

double numero_9[25] =    
   {0, 1, 1, 1, 0,
    0, 0, 0, 1, 0,
    0, 1, 1, 1, 0,
    0, 1, 0, 1, 0,
    0, 1, 1, 1, 0};

double numero_0[25] =    
   {0, 1, 1, 1, 0, 
    0, 1, 0, 1, 0, 
    0, 1, 0, 1, 0, 
    0, 1, 0, 1, 0, 
    0, 1, 1, 1, 0,};

double *sprites[10] = {numero_0, numero_1, numero_2, numero_3, numero_4, numero_5, numero_6, numero_7, numero_8, numero_9};                         

// Função para exibir um número na matriz
void exibir_numero(double *desenho) {
    for (int i = 0; i < NUM_PIXELS; i++) {
        uint valor_led = matrix_rgb(desenho[i] * 0.1, desenho[i] * 0.1, desenho[i] * 0.1);
        pio_sm_put_blocking(pio, sm, valor_led);
    }
}

// Função de debounce e callback dos botões
void callback_button(uint botao, uint32_t events) {
    uint time = to_ms_since_boot(get_absolute_time());
    if (time - last_time > 250) {  // Debounce de 250ms
        last_time = time;
        if (botao == BOTAO_A_PIN) {
            id = (id + 1) % 10;  // Incrementa id e garante que ele vai de 0 a 9
        } else if (botao == BOTAO_B_PIN) {
            id = (id + 9) % 10;  // Decrementa id e garante que ele vai de 0 a 9
        }
        exibir_numero(sprites[id]);
        printf("Número exibido: %d\n", id);
    }
}

// Configuração de GPIOs
void setup() {
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    
    gpio_init(BOTAO_A_PIN);
    gpio_set_dir(BOTAO_A_PIN, GPIO_IN);
    gpio_pull_up(BOTAO_A_PIN);
    gpio_init(BOTAO_B_PIN);
    gpio_set_dir(BOTAO_B_PIN, GPIO_IN);
    gpio_pull_up(BOTAO_B_PIN);
    
    gpio_init(LED_PIN_RED);
    gpio_set_dir(LED_PIN_RED, GPIO_OUT);
    gpio_init(LED_PIN_GREEN);
    gpio_set_dir(LED_PIN_GREEN, GPIO_OUT);
    gpio_init(LED_PIN_BLUE);
    gpio_set_dir(LED_PIN_BLUE, GPIO_OUT);
    
    gpio_set_irq_enabled_with_callback(BOTAO_A_PIN, GPIO_IRQ_EDGE_FALL, true, &callback_button);
    gpio_set_irq_enabled_with_callback(BOTAO_B_PIN, GPIO_IRQ_EDGE_FALL, true, &callback_button);
}

// Função para piscar os LEDs
void piscar_leds(int led, int tempo) {
    gpio_put(led, 1);
    sleep_ms(tempo);
    gpio_put(led, 0);
    sleep_ms(tempo);
}

// Função para desligar a matriz de LEDs
void desligar_matriz() {
    for (int i = 0; i < NUM_PIXELS; i++) {
        pio_sm_put_blocking(pio, sm, matrix_rgb(0, 0, 0)); // Envia cor preta para todos os LEDs
    }
}


// Loop principal
int main() {
    set_sys_clock_khz(128000, false);
    stdio_init_all();
    setup();
    
    pio = pio0;
    uint offset = pio_add_program(pio, &pio_matrix_program);
    sm = pio_claim_unused_sm(pio, true);
    pio_matrix_program_init(pio, sm, offset, LED_PIN);
    
    desligar_matriz();
    
    while (true) {
        piscar_leds(LED_PIN_RED, 200);
    }
}
