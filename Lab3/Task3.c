#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/timer.h"
#include "hardware/clocks.h"
#include "hardware/uart.h"
#include "hardware/adc.h"
#include "hardware/pwm.h"

int64_t alarm_callback(alarm_id_t id, void *user_data) {
    // Put your timeout handler code in here
    return 0;
}


// UART defines
// // By default the stdout UART is `uart0`, so we will use the second one
// #define UART_ID uart1
// #define BAUD_RATE 115200

// // Use pins 4 and 5 for UART1
// // Pins can be changed, see the GPIO function select table in the datasheet for information on GPIO assignments
// #define UART_TX_PIN 4
// #define UART_RX_PIN 5



int main()
{
    stdio_init_all();
    sleep_ms(2000);

    adc_init();
    adc_gpio_init(26);


        //Task3.1
        //adc_set_temp_sensor_enabled(1);


    printf("ADC Example, measuring GPIO26\n");


    // Make sure GPIO is high-impedance, no pullups etc
    //adc_gpio_init(26);
    // Select ADC input 0 (GPIO26)
    adc_select_input(0);


    // Timer example code - This example fires off the callback after 2000ms
    // add_alarm_in_ms(2000, alarm_callback, NULL, false);
    // For more examples of timer use see https://github.com/raspberrypi/pico-examples/tree/master/timer

    // printf("System Clock Frequency is %d Hz\n", clock_get_hz(clk_sys));
    // printf("USB Clock Frequency is %d Hz\n", clock_get_hz(clk_usb));
    // For more examples of clocks use see https://github.com/raspberrypi/pico-examples/tree/master/clocks

    // Set up our UART
    // uart_init(UART_ID, BAUD_RATE);
    // // Set the TX and RX pins by using the function select on the GPIO
    // // Set datasheet for more information on function select
    // gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART);
    // gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);
    
    // Use some the various UART functions to send out data
    // In a default system, printf will also output via the default UART
    
    // Send out a string, with CR/LF conversions
    // uart_puts(UART_ID, " Hello, UART!\n");
    
    // For more examples of UART use see https://github.com/raspberrypi/pico-examples/tree/master/uart

    //Task3.2
        // Tell GPIO 0 and 1 they are allocated to the PWM
        int LED = 0;
        int KNOB_LEVEL = 100;
        gpio_set_function(LED, GPIO_FUNC_PWM);
    
        // Find out which PWM slice is connected to GPIO 0 (it's slice 0)
        uint slice_num = pwm_gpio_to_slice_num(LED);
    
        //pwm_config_set_wrap(slice_num,4095);
        
        // Set period of 4 cycles (0 to 3 inclusive)
        pwm_set_wrap(slice_num,4095);
        pwm_set_enabled(slice_num, true);

        // Set channel A output high for one cycle before dropping
        

   



    while (true) {
        //Task 3.2
        uint16_t KNOB_LEVEL = adc_read();
        pwm_set_gpio_level(LED, KNOB_LEVEL);


        printf("KNOB duty cycle: %d/4095", KNOB_LEVEL);
        sleep_ms(10);




        // Task3.1
        // uint16_t result = adc_read();
        

        // float ADC_Voltage = (result * 3.3f) / 4095.0f;
        // //int ADC_Voltage = result * 1;
        // float Temp = 27.0f - ((ADC_Voltage - 0.706f)/0.001721f);

        // printf("Raw value: 0x%03x, voltage: %.3f V, temp (C): %.3f\n", result, ADC_Voltage, Temp);
        // sleep_ms(500);
    }
}

//T = 27 - (ADC_Voltage - 0.706)/0.00172
