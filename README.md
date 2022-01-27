# ReConstructibles
ReConstructibles are physically reconfigurable shape-changing interfaces. 
This repository is used to manage the hardware and software architecture of these devices.

## Setup

### M5 Stamp
Download the USB-TTL driver from [this link](https://docs.m5stack.com/en/quick_start/stamp_pico/arduino). 
The downloader that came with the STAMP-PICO kit is CH9102.
Install the driver on your computer.

- MacOS prevents automatically installing the driver with a warning message.
Permission must be explicitly granted in System Preferences > Security & Privacy

### Tiny Pico

#### Breadboard Setup
Connect the following pins on the 1.3" display to the TinyPico's SPI interface:

| 1.3" Display Pin | TinyPico Pin |
| ---------------- | ------------ |
| Vin              | 3.3V output  |
| GND              | GND          |
| SCK              | #18 (SPI clk)|
| SO               | #23 (MISO)   |
| SI               | #19 (MOSI)   |
| TCS              | #5 (SPI SS)  |
| RST              | #26 (I/O)    |
| D/C              | #25 (I/O)    |

#### Arduino Setup
1. Install the [Arduinio IDE](https://www.arduino.cc/en/software)
1. Download and install ESP32 libraries for working with TinyPico
    1. Navigate to Arduino > Preferences
    1. Input `https://dl.espressif.com/dl/package_esp32_index.json` under "Additional Boards Manager URLs"
    1. Click "OK"
    1. Navigate to Tools > Board > Boards Manager
    1. Search "esp32" and install the esp32 package by Espressif Systems 
        - This project used v1.0.6 at time of writing this guide, but the latest version should be fine
    1. Navigate to Tools > Manage Libraries
    1. Search "TinyPico" and install the "TinyPICO Helper Library" package by UnexpectedMaker
        - This project used v1.4.0 at time of writing this guide, but the latest version should be fine
    1. Close the Library Manager
1. Connect TinyPico board to computer via MicroUSB cable
1. Select the TinyPico Board and port
    1. Select Tools > Board > ESP32 Arduino > TinyPico
    1. Select Tools > Port > [USB serial port name]


#### 1.3" Display Graphics Test