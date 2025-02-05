#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "hardware/pio.h"
#include "hardware/uart.h"
#include "pico/bootrom.h"
#include "lib/ssd1306.h"
#include "lib/font.h"

#include "ws2812.pio.h"

// Váriaveis para os pinos do LED RGB
#define LED_GREEN 11
#define LED_BLUE 12
#define LED_RED 13

// Variáveis para a matriz de LEDs
#define MATRIX_PIN 7
#define NUM_LEDS 25

// Variáveis para os pinos dos botões
#define BUTTON_A 5
#define BUTTON_B 6

// Variáveis globais para o controle PIO
// Variáveis globais para PIO
static PIO  pio = pio0;
static uint sm  = 0;

// Variáveis para a comunicação I2C
#define I2C_PORT i2c1
#define I2C_SDA 8
#define I2C_SCL 9
#define endereco 0x3C

/*
#define UART_ID uart1
#define BAUD_RATE 115200

#define UART_TX_PIN 4
#define UART_RX_PIN 5
*/



int main() {
    stdio_init_all();

    // I2C Initialisation. Using it at 400Khz.
    i2c_init(I2C_PORT, 400*1000);
    
    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SDA);
    gpio_pull_up(I2C_SCL);

    // Inicializa o PIO (ws2812_program)
    uint offset = pio_add_program(pio, &ws2812_program);
    sm = pio_claim_unused_sm(pio, true);
    ws2812_program_init(pio, sm, offset, MATRIX_PIN);

    /*
    uart_init(UART_ID, BAUD_RATE);
    
    gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART);
    gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);
    
    uart_puts(UART_ID, " Hello, UART!\n");
    */
    
    while (true) {
        printf("Hello, world!\n");
        sleep_ms(1000);
    }
}