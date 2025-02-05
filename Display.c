#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "ws2812.pio.h"
#include "lib/ssd1306.h"
#include "lib/font.h"
#include "lib/number_matrix.h"

// Váriaveis para os pinos do LED RGB
#define LED_GREEN 11
#define LED_BLUE 12
#define LED_RED 13

// Estado dos LEDs
bool state_green_led = false;
bool state_blue_led = false;

// Variáveis para os pinos dos botões
#define BUTTON_A 5
#define BUTTON_B 6

// Debounce time
#define DEBOUNCE_TIME 200  // 200 ms

// Último tempo de pressionamento dos botões
volatile uint32_t last_press_time_A = 0;
volatile uint32_t last_press_time_B = 0;

// Variáveis para a matriz de LEDs
#define MATRIX_PIN 7
#define NUM_LEDS 25

// Variável global para cor atual
uint32_t color;

// Variáveis globais para o controle PIO
static PIO  pio = pio0;
static uint sm  = 0;

/*
// Variáveis para a comunicação I2C
#define I2C_PORT i2c1
#define I2C_SDA 8
#define I2C_SCL 9
#define endereco 0x3C
*/

// Função para configurar os pinos
static void configure_gpio() {
    // Configura os LEDs RGB
    gpio_init(LED_GREEN);
    gpio_init(LED_BLUE);
    gpio_init(LED_RED);
    gpio_set_dir(LED_GREEN, GPIO_OUT);
    gpio_set_dir(LED_BLUE, GPIO_OUT);
    gpio_set_dir(LED_RED, GPIO_OUT);

    // Configura os botões como pull-up
    gpio_init(BUTTON_A);
    gpio_init(BUTTON_B);    
    gpio_set_dir(BUTTON_A, GPIO_IN);
    gpio_set_dir(BUTTON_B, GPIO_IN);
    gpio_pull_up(BUTTON_A);
    gpio_pull_up(BUTTON_B);

    /*
    // I2C Initialisation. Using it at 400Khz.
    i2c_init(I2C_PORT, 400 * 1000);

    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C); // Set the GPIO pin function to I2C
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C); // Set the GPIO pin function to I2C
    gpio_pull_up(I2C_SDA); // Pull up the data line
    gpio_pull_up(I2C_SCL); // Pull up the clock line

    ssd1306_t ssd; // Inicializa a estrutura do display
    ssd1306_init(&ssd, WIDTH, HEIGHT, false, endereco, I2C_PORT); // Inicializa o display
    ssd1306_config(&ssd); // Configura o display
    ssd1306_send_data(&ssd); // Envia os dados para o display

    // Limpa o display. O display inicia com todos os pixels apagados.
    ssd1306_fill(&ssd, false);
    ssd1306_send_data(&ssd);
    */
}

// Função para converter a intensidade de cada canal G, R, B em 24 bits
uint32_t matrix_rgb(double g, double r, double b) {
    unsigned char G = (unsigned char)(g * 255.0);
    unsigned char R = (unsigned char)(r * 255.0);
    unsigned char B = (unsigned char)(b * 255.0);

    return ( (uint32_t)G << 24 ) |
           ( (uint32_t)R << 16 ) |
           ( (uint32_t)B <<  8 );
}

// Função para exibir números na matriz de LEDs
void display_number(char number) {
    for (int i = 0; i < NUM_LEDS; i++) {
        double intensity = number_matrix[number][i]; // Intensidade do LED
        color = matrix_rgb(0, intensity, 0); // Ciano
        pio_sm_put_blocking(pio, sm, color);
    }
}

// Callback para interrupções dos botões
void button_irq_handler(uint gpio, uint32_t events) {
    uint32_t current_time = to_ms_since_boot(get_absolute_time());

    if (gpio == BUTTON_A) { // Liga/Desliga o LED Verde
        if (current_time - last_press_time_A > DEBOUNCE_TIME) {
            last_press_time_A = current_time;  // Atualiza o tempo da última pressão
            state_green_led = !state_green_led;  // Alterna o estado
            gpio_put(LED_GREEN, state_green_led);
            printf("Botão A pressionado. LED Verde: %d\n", state_green_led);
        }
    } 
    else if (gpio == BUTTON_B) { // Liga/Desliga o LED Azul
        if (current_time - last_press_time_B > DEBOUNCE_TIME) {
            last_press_time_B = current_time;  // Atualiza o tempo da última pressão
            state_blue_led = !state_blue_led;  // Alterna o estado
            gpio_put(LED_BLUE, state_blue_led);
            printf("Botão B pressionado. LED Azul: %d\n", state_blue_led);
        }
    }
}

int main() {
    stdio_init_all();
    configure_gpio();

    // Configurando o clock do sistema para operar em 100MHz
    set_sys_clock_khz(100000, false);

    // Inicializa o PIO (ws2812_program)
    uint offset = pio_add_program(pio, &ws2812_program);
    sm = pio_claim_unused_sm(pio, true);
    ws2812_program_init(pio, sm, offset, MATRIX_PIN);

    // Configura as interrupções para os botões
    gpio_set_irq_enabled_with_callback(BUTTON_A, GPIO_IRQ_EDGE_FALL, true, &button_irq_handler);
    gpio_set_irq_enabled_with_callback(BUTTON_B, GPIO_IRQ_EDGE_FALL, true, &button_irq_handler);
    
    while (true) {
        if (stdio_usb_connected()) { // Certifica-se de que o USB está conectado
            printf("Digite um caracter: \n");
            char character;
            if (scanf("%c", &character) == 1) { // Lê caractere da entrada padrão
                printf("Valor digitado: '%c'\n", character);

                switch (character) {
                    case '0': {
                        display_number(0);
                        break;
                    }
                    case '1': {
                        display_number(1);
                        break;
                    }
                    case '2': {
                        display_number(2);
                        break;
                    }
                    case '3': {
                        display_number(3);
                        break;
                    }
                    case '4': {
                        display_number(4);
                        break;
                    }
                    case '5': {
                        display_number(5);
                        break;
                    }
                    case '6': {
                        display_number(6);
                        break;
                    }
                    case '7': {
                        display_number(7);
                        break;
                    }
                    case '8': {
                        display_number(8);
                        break;
                    }
                    case '9': {
                        display_number(9);
                        break;
                    }
                    default: {
                        printf("Caracter inválido!\n");
                        break;
                    }
                }
            }
        }
        sleep_ms(100);
    }
}