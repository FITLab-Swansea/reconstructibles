/*
 * reconstructibles - ReConstructibles Library
 */

#include "reconstructibles.h"

// System constants
#define DEBUG_ON 1

// System data
uint8_t thisNumPresses;
uint8_t otherNumPresses;

// System hardware
Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);

void setup() 
{
  // Initialize debug system
  setDebug(true);
  setSerial(9600);
  
  // Initialize variables
  thisNumPresses = 0;
  otherNumPresses = 0;
  
  // Set up display
  debug_SerialPrintln("\nInitializing TFT display...");
  tft.init(240,240);
  displayInitialCount();
  
  // TODO: Set up capacitive sensor
  // TODO: Set up serial connection
}

void loop() 
{
  // TODO: Check for touch and listen for other device
  // TODO: If touched, signal other device
  // TODO: If touched, update display
  // TODO: If data received, update display

  // TODO: Randomly disconnect Serial (indicate separation)
  // TODO: Reconnect
}

// Display Functions
void clearDisplay() 
{
  tft.fillScreen(ST77XX_BLACK);
}

// Display initial press count table
void displayInitialCount()
{
  clearDisplay();
  drawTableLines();
  drawTableHeader();
  drawTableBody();
}

// Draw white lines for press count table
void drawTableLines() {
  tft.drawLine(TFT_WIDTH/2, 0, TFT_WIDTH/2, TFT_HEIGHT, ST77XX_WHITE);
  tft.drawLine(0, TFT_HEIGHT/3, TFT_WIDTH, TFT_HEIGHT/3, ST77XX_WHITE);
}

#define TABLE_HEADER_TEXT_SIZE 4

// Print press count table column headers
void drawTableHeader() {
    // Table headers
  tft.setTextSize(TABLE_HEADER_TEXT_SIZE);
  // - Me
  tft.setCursor(TFT_WIDTH/6,TFT_HEIGHT/9);
  tft.setTextColor(ST77XX_RED, ST77XX_BLACK);
  tft.print("ME");
  // - Them
  tft.setCursor(5*TFT_WIDTH/9,TFT_HEIGHT/9);
  tft.setTextColor(ST77XX_BLUE, ST77XX_BLACK);
  tft.print("THEM");
}

#define TABLE_BODY_TEXT_SIZE 9

// Print press counts
void drawTableBody() {
    // TODO: setTextSize should be inside each draw function, but without repeating work
    tft.setTextSize(TABLE_BODY_TEXT_SIZE); 
    drawMyCount();
    drawOtherCount();
}

// Print press count of this device
void drawMyCount() {
  tft.setCursor(TFT_WIDTH/6,TFT_HEIGHT/2); 
  tft.setTextColor(ST77XX_RED, ST77XX_BLACK);
  tft.print(thisNumPresses);
}

// Print press count of other device
void drawOtherCount() {
  tft.setCursor(2*TFT_WIDTH/3,TFT_HEIGHT/2);
  tft.setTextColor(ST77XX_BLUE, ST77XX_BLACK);
  tft.print(otherNumPresses);
}
