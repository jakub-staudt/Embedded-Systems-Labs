# Raspberry Pi Pico 2 W – Laboratory Projects

A collection of embedded systems laboratory exercises developed using the **Raspberry Pi Pico 2 W** platform.  
The projects focus on low-level embedded programming, hardware interfacing, communication protocols, and real-time systems concepts.  
The classes were prepared by the instructor Mateusz Szpetkowski from Wrocław University of Science & Technology.

---

## Preview

![Raspberry Pi Pico 2 W development board](images/raspberry-pi-pico-2w.jpeg)

---

## About

These laboratory projects were created as part of embedded systems coursework using the **Raspberry Pi Pico 2 W** microcontroller board based on the RP2350 architecture.

The exercises introduce practical aspects of:
- Embedded C/C++ programming
- GPIO and peripheral control
- Hardware communication protocols
- Sensor interfacing
- Wireless embedded applications

---

# Laboratory Exercises

# Laboratory Topics

## Lab 2 – Clock Tree and Hardware Timers (RP2350)

Focus on low-level clock management and asynchronous timing mechanisms inside the RP2350 microcontroller.

### Topics Covered
- RP2350 Clock System
- Clock Frequency Reading
- External Crystal Oscillator (XOSC)
- PLL Configuration and Reconfiguration
- Hardware Timers
- Non-blocking Embedded Systems
- Edge Detection
- Button Debouncing
- UART Debugging

### Key Concepts
- Reading and modifying `clk_sys`, `clk_peri`, and `clk_usb`
- Switching clock sources safely
- Configuring PLL to custom frequencies
- Replacing blocking delays with hardware timers
- Building responsive embedded applications

---

## Lab 3 – ADC and PWM

Introduction to analog-to-digital conversion and hardware PWM signal generation.

### Topics Covered
- ADC (Analog-to-Digital Converter)
- PWM (Pulse Width Modulation)
- Internal Temperature Sensor
- Potentiometer Input
- LED Brightness Control
- Software Noise Filtering

### Key Concepts
- Reading RP2350 internal temperature sensor
- Voltage-to-temperature conversion
- PWM duty cycle control
- Real-time potentiometer dimming
- ADC signal filtering and stabilization

---

## Lab 4 – I2C Communication (SHT30 Sensor on RP2350)

Implementation of I2C communication and environmental sensor interfacing.

### Topics Covered
- I2C Bus Communication
- Master-Slave Architecture
- SHT30 Temperature & Humidity Sensor
- Bitwise Operations
- MSB / LSB Data Handling
- Hardware Polling

### Key Concepts
- I2C device scanning
- Sensor command transmission
- Multi-byte data acquisition
- Bit shifting and byte reconstruction
- Raw sensor data conversion
- Continuous environmental monitoring

---

## Lab 5 – Advanced I2C

Advanced peripheral integration using multiple I2C devices and buses.

### Topics Covered
- EEPROM Communication
- IMU (Accelerometer)
- OLED SSD1306 Display
- Multi-device I2C Systems
- Multi-bus Configuration

### Key Concepts
- Non-volatile memory operations
- Reading accelerometer axis data
- Signed integer reconstruction (`int16_t`)
- OLED graphical output
- Real-time sensor dashboards
- I2C bus separation (`i2c0` and `i2c1`)
---

# Technologies Used

- Raspberry Pi Pico 2 W
- RP2350 Microcontroller
- Embedded C/C++
- VS Code
- UART / SPI / I2C
- GPIO Programming
- ADC Interfaces
- Serial Debugging

---

# Related Website

https://edge-intelligence.pl

