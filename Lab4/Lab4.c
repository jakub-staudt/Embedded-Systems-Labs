#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "hardware/uart.h"
#include "hardware/i2c.h"

// I2C defines
// This example will use I2C0 on GPIO8 (SDA) and GPIO9 (SCL) running at 400KHz.
// Pins can be changed, see the GPIO function select table in the datasheet for information on GPIO assignments
#define I2C_PORT i2c0
#define I2C_SDA 4
#define I2C_SCL 5

// UART defines
// By default the stdout UART is `uart0`, so we will use the second one
// #define UART_ID uart1
// #define BAUD_RATE 115200

// Use pins 4 and 5 for UART1
// Pins can be changed, see the GPIO function select table in the datasheet for information on GPIO assignments
// #define UART_TX_PIN 4
// #define UART_RX_PIN 5

// These are any addresses of the form 000 0xxx or 111 1xxx
bool reserved_addr(uint8_t addr) {
    return (addr & 0x78) == 0 || (addr & 0x78) == 0x78;
}

int main()
{
    stdio_init_all();

    // I2C Initialisation. Using it at 100Khz.
    i2c_init(i2c0, 100*1000);
    
    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SDA);
    gpio_pull_up(I2C_SCL);
    // For more examples of I2C use see https://github.com/raspberrypi/pico-examples/tree/master/i2c


    for (int addr = 0; addr < (1 << 7); ++addr) {
        uint8_t rxdata;

        //printf("Sending trigger command...");
        uint8_t cmd[2] = {0x2C, 0x06};
        //send on 0x44 address
        int ret = i2c_write_blocking(i2c0, 0x44, cmd, 2, false);

        //printf("Wrote 2 bytes. Sensor started measurement.");
        sleep_ms(15);

        uint8_t read_data[6];

        i2c_read_blocking(i2c0, 0x44, read_data, 6, false);

        printf("0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x\n", read_data[0], read_data[1], read_data[2], read_data[3], read_data[4],read_data[5],read_data[6]);
  
        if (ret >= 0) {
            // printf("0x%02x ", addr);
        }

        if (ret == 2) {
            printf("Success: command sent\n");
        } else {
            printf("Error: wrote %d bytes\n", ret);
        }
 

        // Task3
        uint16_t raw_temp = (read_data[0] << 8) | read_data[1];
        uint16_t raw_hum = (read_data[3] << 8) | read_data[4];

        printf("Temperature: %u\n",raw_temp);
        printf("Humidity: %u\n",raw_hum);
        

        //Task 4
        float converted_temp = -45 + (175 * raw_temp / 65535);
        float converted_hum = 100 * raw_hum / 655;

        printf("[SHT30] Temperature: %0.2f | Humidity: %0.2f\n", converted_temp, converted_hum);
        

        sleep_ms(1000);

        // Perform a 1-byte dummy read from the probe address. If a slave
        // acknowledges this address, the function returns the number of bytes
        // transferred. If the address byte is ignored, the function returns
        // -1.
 
        // Skip over any reserved addresses.
        
        // if (reserved_addr(addr))
        //     ret = PICO_ERROR_GENERIC;
        // else
            //foUND ADDRESS
            
 
        // printf(ret < 0 ? "." : "%02x",addr);
        // printf(addr % 16 == 15 ? "\n" : "  ");
    }
    printf("Done.\n");


    // // Set up our UART
    // uart_init(UART_ID, BAUD_RATE);
    // // Set the TX and RX pins by using the function select on the GPIO
    // // Set datasheet for more information on function select
    // gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART);
    // gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);
    
    // // Use some the various UART functions to send out data
    // // In a default system, printf will also output via the default UART
    
    // // Send out a string, with CR/LF conversions
    // uart_puts(UART_ID, " Hello, UART!\n");
    
    // For more examples of UART use see https://github.com/raspberrypi/pico-examples/tree/master/uart

    while (true) {
        // printf("Hello, world!\n");
        // sleep_ms(1000);
    }
}
