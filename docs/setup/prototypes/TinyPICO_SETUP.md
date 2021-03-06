# TinyPICO Setup

Follow these instructions for setting up the TinyPICO boards and 1.3" TFT displays for prototype development.

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

## Arduino Setup
1. Install the [Arduinio IDE](https://www.arduino.cc/en/software)
1. Download and install ESP32 libraries for working with TinyPico
    1. Navigate to Arduino > Preferences
    1. Input `https://dl.espressif.com/dl/package_esp32_index.json` under "Additional Boards Manager URLs"
    1. Click "OK"
    1. Navigate to Tools > Board > Boards Manager
    1. Search "esp32" and install the esp32 library by Espressif Systems 
        - This project used v1.0.6 at time of writing this guide, but the latest version should be fine
    1. Navigate to Tools > Manage Libraries
    1. Search "TinyPico" and install the "TinyPICO Helper Library" by UnexpectedMaker
        - This project used v1.4.0 at time of writing this guide, but the latest version should be fine
    1. Close the Library Manager
1. Connect TinyPico board to computer via MicroUSB cable
1. Select the TinyPico Board and port
    1. Select Tools > Board > ESP32 Arduino > TinyPico
    1. Select Tools > Port > [USB serial device name]

## Tests

### 1.3" Display Graphics Test
1. Install the Arduino libraries for working with the TFT display.
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
1. Open and run the [`graphicstest`](/tests/graphicstest/graphicstest.ino) example sketch located in the [`/tests/` folder](/tests/).
    - This is the `graphicstest` provided by the Adafruit ST7735 and ST7789 Library (File > Examples > Adafruit ST7735 and ST7789 Library > graphicstest) with modifications to run correctly with the TinyPICO setup described above.
