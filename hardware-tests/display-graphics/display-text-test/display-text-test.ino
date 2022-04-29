#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library for ST7735
#include <Adafruit_ST7789.h> // Hardware-specific library for ST7789
#include <SPI.h>

// Helper functions
#define SerialPrintln(x) (Serial.println(F(x)))
#define SerialPrint(x) (Serial.print(F(x)))
#define SerialNewline() (Serial.println())

// Large texts for pushing limits of display
#define DARTH_PLAGUEIS "Did you ever hear the tragedy of Darth Plagueis The Wise? I thought not. It’s not a story the Jedi would tell you. It’s a Sith legend. Darth Plagueis was a Dark Lord of the Sith, so powerful and so wise he could use the Force to influence the midichlorians to create life… He had such a knowledge of the dark side that he could even keep the ones he cared about from dying. The dark side of the Force is a pathway to many abilities some consider to be unnatural. He became so powerful… the only thing he was afraid of was losing his power, which eventually, of course, he did. Unfortunately, he taught his apprentice everything he knew, then his apprentice killed him in his sleep. Ironic. He could save others from death, but not himself."
#define LOREM_IPSUM "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Curabitur adipiscing ante sed nibh tincidunt feugiat. Maecenas enim massa, fringilla sed malesuada et, malesuada sit amet turpis. Sed porttitor neque ut ante pretium vitae malesuada nunc bibendum. Nullam aliquet ultrices massa eu hendrerit. Ut sed nisi lorem. In vestibulum purus a tortor imperdiet posuere. "

// For the breakout board, you can use any 2 or 3 pins.
#define TFT_CS    5  // Chip select pin = SS on TinyPico
#define TFT_RST   26 // Or set to -1 and connect to Arduino RESET pin
#define TFT_DC    25 
#define TFT_MOSI  19 // Data out
#define TFT_SCLK  18 // Clock out

// Initialize the display
Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);

void setup(void) {
  Serial.begin(9600);
  SerialNewline();
  SerialPrintln("Begin Overflow Test");

  SerialPrintln("\tInitializing TFT display...");
  tft.init(240, 240); // Init ST7789 240x240 1.3" display
  SerialPrintln("\tDone.");
  
  delay(500);
  
  // print large block of text
  clearScreenBlack();
  tftDrawText(DARTH_PLAGUEIS, ST77XX_WHITE);
  delay(1000);

  SerialPrintln("Overflow Test Done");
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
  tft.setTextSize(3);     // CHANGE text size to explore how the display responds
  tft.setTextColor(color);
  tft.setTextWrap(true);
  tft.print(text);
}
