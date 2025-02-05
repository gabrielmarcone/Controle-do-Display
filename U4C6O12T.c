#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "hardware/pio.h"
#include "hardware/uart.h"
#include "pico/bootrom.h"
#include "lib/ssd1306.h"
#include "lib/font.h"

#include "ws2812.pio.h"

#define I2C_PORT i2c1
#define I2C_SDA 8
#define I2C_SCL 9

#define UART_ID uart1
#define BAUD_RATE 115200

#define UART_TX_PIN 4
#define UART_RX_PIN 5



int main() {
    stdio_init_all();

    // I2C Initialisation. Using it at 400Khz.
    i2c_init(I2C_PORT, 400*1000);
    
    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SDA);
    gpio_pull_up(I2C_SCL);

    // PIO Blinking example
    PIO pio = pio0;
    uint offset = pio_add_program(pio, &ws2812_program);
    printf("Loaded program at %d\n", offset);

    uart_init(UART_ID, BAUD_RATE);
    
    gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART);
    gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);
    
    uart_puts(UART_ID, " Hello, UART!\n");
    
    while (true) {
        printf("Hello, world!\n");
        sleep_ms(1000);
    }
}