#include "reconstructibles.h"

#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library for ST7735
#include <Adafruit_ST7789.h> // Hardware-specific library for ST7789
#include <SPI.h>

// For the breakout board, you can use any 2 or 3 pins.
#define TFT_CS    5  // Chip select pin = SS on TinyPico
#define TFT_RST   26 // Or set to -1 and connect to Arduino RESET pin
#define TFT_DC    25 

// OPTION 1 (recommended) is to use the HARDWARE SPI pins, which are unique
// to each board and not reassignable. For Arduino Uno: MOSI = pin 11 and
// SCLK = pin 13. This is the fastest mode of operation and is required if
// using the breakout board's microSD card.

// For 1.14", 1.3", 1.54", 1.69", and 2.0" TFT with ST7789:
//Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);

// OPTION 2 lets you interface the display using ANY TWO or THREE PINS,
// tradeoff being that performance is not as fast as hardware SPI above.
#define TFT_MOSI 19  // Data out
#define TFT_SCLK 18  // Clock out

// OR for the ST7789-based displays, we will use this call
Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);


float p = 3.1415926;

void setup(void) {
  Serial.begin(9600);
  SerialNewline();
  SerialPrintln("Begin Scrolling Test");

  SerialPrintln("\tInitializing TFT display...");
  tft.init(240, 240); // Init ST7789 240x240 1.3" display
  SerialPrintln("\tDone.");
  
  delay(500);
  
  // large block of text
  clearScreenBlack();
  tftDrawText(DARTH_PLAGUEIS, ST77XX_WHITE);
  delay(1000);

  SerialPrintln("Scrolling Test Done");
  delay(1000);
}

void loop() {
  delay(10000);
}

void clearScreenBlack() {
  tft.fillScreen(ST77XX_BLACK);
}

void tftDrawText(char *text, uint16_t color) {
  tft.setCursor(0, 0);
//  tft.setTextSize(5);
  tft.setTextColor(color);
  tft.setTextWrap(true);
  tft.print(text);
}
