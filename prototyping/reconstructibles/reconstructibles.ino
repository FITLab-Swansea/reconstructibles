/*
 * reconstructibles - ReConstructibles Library
 */

#include "reconstructibles.h"

// System constants
#define DEBUG_ON 1
#define NUM_CAP_SENSE_SAMPLES 30

// Debug Mode for Printing to Serial Console
#define ENABLE_DEBUG true

#if ENABLE_DEBUG
#define debug_begin(x) (Serial.begin(x))
#define debug_print(x) (Serial.print(x))
#define debug_println(x) (Serial.println(x))
#else   // Set macros to empty to disable Serial printing
#define debug_begin(x) 
#define debug_print(x)
#define debug_println(x)
#endif

// System data
uint8_t thisNumPresses;
uint8_t otherNumPresses;
bool hasContact;

// System hardware
Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);
CapSensor cs_33_32 = CapSensor(33,32);

void setup() 
{
  // Initialize debug system
  debug_begin(9600);
  
  // Initialize variables
  thisNumPresses = 0;
  otherNumPresses = 0;
  
  // Set up display
  debug_println("\nInitializing TFT display...");
  tft.init(240,240);
  displayInitialCount();
  
  // Set up capacitive sensor
  debug_println("\nInitializing capacitive sensor...");
  hasContact = false;
  
  // TODO: Set up serial connection
}

#define TOUCH_THRESHOLD 10000

void loop() 
{
  
  // TODO: Check for touch and listen for other device
  // Check for touch
  long cs_33_32_reading = cs_33_32.readSensor(NUM_CAP_SENSE_SAMPLES);
//  debug_print("CS: ");
//  debug_println(cs_33_32_reading);
  // TODO: This is a bit buggy, sometimes doesn't register touches
  if ((cs_33_32_reading > TOUCH_THRESHOLD) && (!hasContact))
  {
      debug_println(F("CONTACT!"));
      hasContact = true;
      // Update display on touch
      thisNumPresses++;
      drawTableBody();
  } else if ((cs_33_32_reading < TOUCH_THRESHOLD) && (hasContact)) {
      debug_println(F("released"));
      hasContact = false;
  }
  // TODO: If touched, signal other device
  
  // TODO: If data received, update display

  // TODO: Randomly disconnect Serial (indicate separation)
  // TODO: Reconnect

  delay(10);
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
void drawTableLines() 
{
  tft.drawLine(TFT_WIDTH/2, 0, TFT_WIDTH/2, TFT_HEIGHT, ST77XX_WHITE);
  tft.drawLine(0, TFT_HEIGHT/3, TFT_WIDTH, TFT_HEIGHT/3, ST77XX_WHITE);
}

#define TABLE_HEADER_TEXT_SIZE 4

// Print press count table column headers
void drawTableHeader() 
{
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
void drawTableBody() 
{
    // TODO: setTextSize should be inside each draw function, but without repeating work
    // TODO: Adjust for double-digits, roll-over before three digits
    tft.setTextSize(TABLE_BODY_TEXT_SIZE); 
    drawMyCount();
    drawOtherCount();
}

// Print press count of this device
void drawMyCount() 
{
  tft.setCursor(TFT_WIDTH/6,TFT_HEIGHT/2); 
  tft.setTextColor(ST77XX_RED, ST77XX_BLACK);
  tft.print(thisNumPresses);
}

// Print press count of other device
void drawOtherCount() 
{
  tft.setCursor(2*TFT_WIDTH/3,TFT_HEIGHT/2);
  tft.setTextColor(ST77XX_BLUE, ST77XX_BLACK);
  tft.print(otherNumPresses);
}
