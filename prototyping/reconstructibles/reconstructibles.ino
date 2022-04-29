/*
 * reconstructibles - ReConstructibles Library
 */

#include "reconstructibles.h"

// System constants
#define THIS_COLOR ST77XX_RED
#define OTHER_COLOR ST77XX_BLUE

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

// TODO: threshold should be calibrated, not hard-coded
#define TOUCH_THRESHOLD 10000

// System data
uint8_t thisNumPresses;
uint8_t otherNumPresses;
bool hasContact;
bool thisNumRollover;
bool otherNumRollover;

// System hardware
Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);
CapSensor cs_33_32 = CapSensor(33,32);

void setup() 
{
  // Initialize debug system
  debug_begin(19200);
  
  // Initialize variables
  thisNumPresses = 0;
  otherNumPresses = 0;
  thisNumRollover = false;
  otherNumRollover = false;
  
  // Set up display
  debug_println("\nInitializing TFT display...");
  tft.init(240,240);
  displayInitialCount();
  
  // Set up capacitive sensor
  debug_println("\nInitializing capacitive sensor...");
  hasContact = false;
  
  // Set up serial connection
  Serial2.begin(UART_COMM_BAUD, SERIAL_8N1, RX0, TX0);

  // Set up Bluetooth manager
  rbt_start();
}

void loop() 
{
  // Loop checking for touch and signals from other device simultaneously
  
  // 1. Check for touch
  long cs_33_32_reading = cs_33_32.readSensor(NUM_CAP_SENSE_SAMPLES);

  // TODO: This is a bit buggy with alligator clip (doesn't always register touches)
  if ((cs_33_32_reading > TOUCH_THRESHOLD) && (!hasContact))
  {
      debug_println(F("CONTACT!"));
      hasContact = true;
      // Update display on touch
      incThisNumPresses();
      drawTableBody();
      // Signal other device
      signalTouchEvent();
  } else if ((cs_33_32_reading < TOUCH_THRESHOLD) && (hasContact)) {
      debug_println(F("released"));
      hasContact = false;
  }

  if (incomingNumPresses != otherNumPresses)
  {
    otherNumPresses = incomingNumPresses;
    drawTableBody();
  }

  // 2. Check for serial signal from other device
//  if (Serial2.available())
//  {
//    debug_println(F("-- touched other --"));
//    if (1 == Serial2.read())
//    {
//      // If touch event received, update display
//      incOtherNumPresses();
//      drawTableBody();
//    }
//  }

  // TODO: Randomly disconnect Serial (indicate separation)
  // TODO: Reconnect

  delay(10);
}

// *****************************
// Communication Functions
// *****************************
void signalTouchEvent()
{
//  Serial2.write(1);
//  Serial2.flush();
  rbt_sendData(thisNumPresses);
}

// *****************************
// Data Functions
// *****************************

// Increment num presses for this device
// - Rollover at 99 to avoid printing three digits
void incThisNumPresses()
{
  thisNumPresses++;
  if (thisNumPresses > 99)
  {
    thisNumPresses = 0;
    thisNumRollover = true;
  }
}

// Increment num presses for other device
// - Rollover at 99 to avoid printing three digits
void incOtherNumPresses()
{
  otherNumPresses++;
  if (otherNumPresses > 99)
  {
    otherNumPresses = 0;
    otherNumRollover = true;
  }
}

// *****************************
// Bluetooth Functions
// *****************************

// Callback when data is sent
void rbt_cbOnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) 
{
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}

// Callback when data is received
void rbt_cbOnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len)
{
  memcpy(&incomingDataPacket, incomingData, sizeof(incomingDataPacket));
  Serial.print("Bytes received: ");
  Serial.println(len);
  incomingNumPresses = incomingDataPacket.num_presses;
}

void rbt_start()
{
  // Initialize data
  incomingNumPresses = 0;
  
  // Initialize WiFi and ESP-NOW hardware
  WiFi.mode(WIFI_STA);
  if (esp_now_init() != ESP_OK)
  {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  // Register send data callback
  esp_now_register_send_cb(rbt_cbOnDataSent);

  // Receiver device must be set as ESP-NOW peer to enable connection
  // - Register receiver
  memcpy(peerInfo.peer_addr, RECEIVER_ADDR, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;
  // - Add as peer  
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }
  
  // Register data received callback
  esp_now_register_recv_cb(rbt_cbOnDataRecv);
}

void rbt_sendData(uint8_t d)
{
  outgoingDataPacket.num_presses = d;
  esp_err_t result = esp_now_send(RECEIVER_ADDR, (uint8_t *) &outgoingDataPacket, sizeof(outgoingDataPacket));
   
  if (result == ESP_OK) {
    Serial.println("Sent with success");
  }
  else {
    Serial.print(result);
    Serial.println("Error sending the data"); 
  }
}

// *****************************
// Display Functions
// *****************************

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
  tft.setTextColor(THIS_COLOR, ST77XX_BLACK);
  tft.print("ME");
  // - Them
  tft.setCursor(5*TFT_WIDTH/9,TFT_HEIGHT/9);
  tft.setTextColor(OTHER_COLOR, ST77XX_BLACK);
  tft.print("THEM");
}

#define TABLE_BODY_TEXT_SIZE 9

// Print press counts
void drawTableBody() 
{
    // TODO: setTextSize should be inside each draw function, but without repeating work
    tft.setTextSize(TABLE_BODY_TEXT_SIZE); 
    drawMyCount();
    drawOtherCount();
}

// Print press count of this device
void drawMyCount() 
{
  // Clear table cell if num rolls over
  if (thisNumRollover)
  {
    tft.fillRect(10, TFT_HEIGHT/2, 100, 63, ST77XX_BLACK); 
    thisNumRollover = false;
  }
  // Adjust for double-digits
  if (thisNumPresses < 10)
  {
    tft.setCursor(TFT_WIDTH/6,TFT_HEIGHT/2);   
  } else 
  {
    tft.setCursor(10, TFT_HEIGHT/2);
  }
  
  tft.setTextColor(THIS_COLOR, ST77XX_BLACK);
  tft.print(thisNumPresses);
}

// Print press count of other device
void drawOtherCount() 
{
  // Clear table cell if num rolls over
  if (otherNumRollover)
  {
    tft.fillRect(130, TFT_HEIGHT/2, 100, 63, ST77XX_BLACK); 
    otherNumRollover = false;
  }
  // Adjust for double-digits
  if (otherNumPresses < 10)
  {
    tft.setCursor(2*TFT_WIDTH/3,TFT_HEIGHT/2);  
  } else
  {
    tft.setCursor(TFT_WIDTH/2+10,TFT_HEIGHT/2);  
  }
  
  tft.setTextColor(OTHER_COLOR, ST77XX_BLACK);
  tft.print(otherNumPresses);
}
