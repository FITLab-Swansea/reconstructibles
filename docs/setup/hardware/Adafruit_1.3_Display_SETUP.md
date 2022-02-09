# Adafruit 1.3" TFT Display Setup

Follow these instructions for setting up the 1.3" TFT displays for prototype development with the TinyPICO.
Before setting up the display, make sure your TinyPICO is configured properly: [TinyPICO Setup](./TinyPICO_SETUP.md).

These instructions are based on the following guides:
- [Adafruit 1.3" Display Arduino Wiring and Test](https://learn.adafruit.com/adafruit-1-3-and-1-54-240-x-240-wide-angle-tft-lcd-displays/arduino-wiring-test)

## Breadboard Setup
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

## Install Arduino Libraries
Install the necessary libraries for working with the display:

1. Navigate to Tools > Manage Libraries
1. Install the following libaries (the version used by this project is given in `()`)"
    1. "Adafruit GFX Library" by Adafruit (v1.10.13)
    1. "Adafruit BusIO" by Adafruit (v1.10.3)
        - This might install automatically as a dependency of the GFX library
    1. "Adafruit Zero DMA" by Adafruit (v1.1.0)
    1. "Adafruit ST7735 and ST7789" by Adafruit (v1.8.2)
    1. "Adafruit seesaw Library" by Adafruit (v1.5.8)
        - This might install automatically as a dependency of the ST7735 and ST7789 library
    1. "Adafruit SPIFlash" by Adafruit (v3.8.0)
    1. "SdFat - Adafruit Fork" by Adafruit (v1.5.1)
        - This might install automatically as a dependency of the SPIFlash library
    1. "Adafruit NeoPixel" by Adafruit (v1.10.3)
        - This might install automatically as a dependency of the SPIFlash library