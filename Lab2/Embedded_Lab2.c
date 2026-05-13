#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/timer.h"
#include "hardware/clocks.h"
#include "hardware/pll.h"

//BUtton and LED GPIO pin numbering
#define LED 15
#define BTN 14


bool previous_button_state = 1;
bool blink = 1;
bool toggle = 1;

// Hardware Timer Callback exercise 6 hint LED
//The blinking of the LED
bool timer_callback(struct repeating_timer *t) {
    bool current_state = gpio_get(LED);
     
    if(toggle){
        gpio_put(LED, !current_state);    
    }

    return true; 
}


int main()
{
    stdio_init_all();
   
    //--- GPIO SETUP
    gpio_init(LED); gpio_set_dir(LED, GPIO_OUT);
    gpio_init(BTN); gpio_set_dir(BTN, GPIO_IN); gpio_pull_up(BTN);

    // timer for the exercise 6 hint  LED 
    struct repeating_timer timer;
    add_repeating_timer_ms(1000, timer_callback, NULL, &timer);


    //Printing the current CLK frequencies
    sleep_ms(3000);
    printf("System Clock Frequency is %d MHz\n", clock_get_hz(clk_sys)/1000000);
    printf("Peripheral Clock Frequency; is %d MHz\n", clock_get_hz(clk_peri)/1000000);
    printf("USB Clock Frequency is %d MHz\n", clock_get_hz(clk_usb)/1000000);
    printf("ADC Clock Frequency is %d MHz\n", clock_get_hz(clk_adc)/1000000);
    printf("REF Clock Frequency is %d MHz\n", clock_get_hz(clk_ref)/1000000);

    //Update system clk frequencies
    clock_configure(clk_sys,
                    CLOCKS_CLK_SYS_CTRL_SRC_VALUE_CLK_REF,
                    0,
                    12 * MHZ,
                    12 * MHZ);
    //Update Peri clock frequencies
    clock_configure(clk_peri,
                     0,
                    CLOCKS_CLK_PERI_CTRL_AUXSRC_VALUE_CLK_SYS,
                    12*MHZ,
                    12*MHZ);
    stdio_init_all();
    sleep_ms(3000);


    //Print the modified clk frequencies
    printf("\n\n===================\nChanged clocks");    
    printf("System Clock Frequency is %d MHz\n", clock_get_hz(clk_sys)/1000000);
    printf("Peripheral Clock Frequency; is %d MHz\n", clock_get_hz(clk_peri)/1000000);
    printf("USB Clock Frequency is %d MHz\n", clock_get_hz(clk_usb)/1000000);
    printf("ADC Clock Frequency is %d MHz\n", clock_get_hz(clk_adc)/1000000);
    printf("REF Clock Frequency is %d MHz\n", clock_get_hz(clk_ref)/1000000);                


    //PLL clock configuraiton
    pll_init(pll_sys, 1, 1536*MHZ, 6, 2);
    clock_configure(clk_sys, CLOCKS_CLK_SYS_CTRL_SRC_VALUE_CLKSRC_CLK_SYS_AUX, CLOCKS_CLK_SYS_CTRL_AUXSRC_VALUE_CLKSRC_PLL_SYS, 128000000, 128000000);

    clock_configure(clk_peri,
                0,
                CLOCKS_CLK_PERI_CTRL_AUXSRC_VALUE_CLK_SYS,
                128 * MHZ,
                128 * MHZ);
    stdio_init_all(); 
    sleep_ms(3000);`


    //Print the clk frequencies after changing PLL clock
    printf("\n\n===================\nChanged clocks");    
    printf("System Clock Frequency is %d MHz\n", clock_get_hz(clk_sys)/1000000);
    printf("Peripheral Clock Frequency; is %d MHz\n", clock_get_hz(clk_peri)/1000000);
    printf("USB Clock Frequency is %d MHz\n", clock_get_hz(clk_usb)/1000000);
    printf("ADC Clock Frequency is %d MHz\n", clock_get_hz(clk_adc)/1000000);
    printf("REF Clock Frequency is %d MHz\n", clock_get_hz(clk_ref)/1000000); 
    
    
    while (true) {
        //Task 6 rising edge detection of the button and printing to the serial monitor


        bool current_button_state = gpio_get(BTN);

        if(current_button_state == false && previous_button_state == true) {
                printf("Button clicked!\n"); 
                sleep_ms(20);
                toggle = !toggle;
            }
        previous_button_state = current_button_state;
    }
}
