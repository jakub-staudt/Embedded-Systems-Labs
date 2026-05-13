// Lab5
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
// #include "hardware/uart.h"
#include "hardware/i2c.h"
#include "ssd1306.h"


// I2C defines
// This example will use I2C0 on GPIO8 (SDA) and GPIO9 (SCL) running at 400KHz.
// Pins can be changed, see the GPIO function select table in the datasheet for information on GPIO assignments
#define I2C_PORT i2c0
#define I2C0_SDA 4 //For Sensor I2C0
#define I2C0_SCL 5 //For Sensor I2C0
#define I2C1_SDA 6 //IMU - I2C1
#define I2C1_SCL 7 //IMU - I2C1
#define EEPROM_ADDR 0x50
#define IMU_ADDR 0x19

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

    // I2C Initialisation. Using it at 400Khz.
    i2c_init(i2c0, 400*1000);
    
    gpio_set_function(I2C0_SDA, GPIO_FUNC_I2C);
    gpio_set_function(I2C0_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(I2C0_SDA);
    gpio_pull_up(I2C0_SCL);
    // For more examples of I2C use see https://github.com/raspberrypi/pico-examples/tree/master/i2c

    uint8_t high_address = 0x00;
    uint8_t low_address = 0x00;

// Lab5 Task 1

    // Writing data array to EEPROM. First two bytes are the address, third byte is the data to be written.
    uint8_t eeprom_write_data[3] = {high_address, low_address, 42};
    uint8_t eeprom_read_address[2] = {high_address, low_address};

    i2c_write_blocking(i2c0, EEPROM_ADDR, eeprom_write_data, 3, false);
    sleep_ms(5);

    //Write address to EEPROM, keep communication open -> non-stop = true
    i2c_write_blocking(i2c0, EEPROM_ADDR, eeprom_read_address, 2, true);

    //Read 1-byte data from EEPROM
    uint8_t eeprom_read_value = 0;
    i2c_read_blocking(i2c0, EEPROM_ADDR, &eeprom_read_value, 1, false);

    printf("Read from EEPROM:  %d\n", eeprom_read_value);
       
    

// Lab5 Task 2
    //Wakeup IMU
    uint8_t cfg[2] = {0x20, 0x77}; // (0x20 is the Control Register, 0x77 turns on all axes at 100Hz). 
    i2c_write_blocking(i2c0, IMU_ADDR, cfg, 2, false);

    //int16_t x = (int16_t)((high_address << 8) | low_address); 



// Lab5 - Task3

    // ---------- i2c1 for OLED ----------
    i2c_init(i2c1, 400 * 1000);

    gpio_set_function(I2C1_SDA, GPIO_FUNC_I2C);
    gpio_set_function(I2C1_SCL, GPIO_FUNC_I2C);

    gpio_pull_up(I2C1_SDA);
    gpio_pull_up(I2C1_SCL);

    // OLED setup
    ssd1306_t disp;
    disp.external_vcc = false;
    ssd1306_init(&disp, 128, 64, 0x3C, i2c1);
    // ssd1306_clear(&disp);

    while (true) {

    //Task2 --BEGIN
        //Start reading from IMU
        uint8_t reg = 0x28 | 0x80;
        //X,Y,Z axis data
        uint8_t data[6] = {0};

        //Write address
        i2c_write_blocking(i2c0, IMU_ADDR, &reg, 1, true);
        //Read data
        i2c_read_blocking(i2c0, IMU_ADDR, data, 6, false);
        int16_t x = (int16_t)((data[1] << 8) | data[0]);
        int16_t y = (int16_t)((data[3] << 8) | data[2]);
        int16_t z = (int16_t)((data[5] << 8) | data[4]);
        
        printf("X: %d, Y: %d, Z: %d\n", x, y, z);
        sleep_ms(100);
    //Task2 --END

    
    //Task3 - BEGIN

        // OLED output
        char buf[32];

        ssd1306_clear(&disp);

        sprintf(buf, "IMU Data");
        ssd1306_draw_string(&disp, 0, 0, 2, buf);

        sprintf(buf, "X: %d", x);
        ssd1306_draw_string(&disp, 0, 16, 2, buf);

        sprintf(buf, "Y: %d", y);
        ssd1306_draw_string(&disp, 0, 32, 2, buf);

        sprintf(buf, "Z: %d", z);
        ssd1306_draw_string(&disp, 0, 48, 2, buf);

        ssd1306_show(&disp);

        sleep_ms(100);
    //Task3 - END

    }
}



