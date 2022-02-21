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

// System data
uint8_t thisNumPresses;
uint8_t otherNumPresses;
bool hasContact;
bool thisNumRollover;
bool otherNumRollover;


// *****************************
// TEMP Bluetooth
// *****************************
// Uncomment address of receiver
//#define BROADCAST_ADDR d1_broadcastAddress
#define BROADCAST_ADDR d2_broadcastAddress

// Variable to store incoming num presses
uint8_t incomingNumPresses;
// Variable to store if sending data was successful
String success;

// struct to hold message
typedef struct struct_message {
  uint8_t presses;
} struct_message;
// struct to store readings
struct_message thisReadings;
// struct to store incoming readings
struct_message incomingReadings;

// Callback when data is sent
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
  if (status ==0){
    success = "Delivery Success :)";
  }
  else{
    success = "Delivery Fail :(";
  }
}

// Callback when data is received
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&incomingReadings, incomingData, sizeof(incomingReadings));
  Serial.print("Bytes received: ");
  Serial.println(len);
  otherNumPresses = incomingReadings.presses;
  drawTableBody();
}
// *****************************
// END TEMP
// *****************************

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

  // *****************************
  // TEMP SETUP
  // *****************************
  WiFi.mode(WIFI_STA);
  if (esp_now_init() != ESP_OK)
  {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  // Once ESP-NOW is successfully initialized, register send callback to
  // get the status of transmitted packet
  esp_now_register_send_cb(OnDataSent);

  // Register ESP-NOW peer
  esp_now_peer_info_t peerInfo;
  // TODO: change broadchast address to receiver address
  memcpy(peerInfo.peer_addr, BROADCAST_ADDR, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;
  
  // Add ESP-NOW peer  
  // -       
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }
  
  // Register data received callback function
  esp_now_register_recv_cb(OnDataRecv);
  // *****************************
  // END TEMP SETUP
  // *****************************
}

// TODO: threshold should be calibrated, not hard-coded
#define TOUCH_THRESHOLD 10000

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
  // *****************************
  // TEMP WIRELESS COMMS
  // *****************************
  thisReadings.presses = thisNumPresses;
  esp_err_t result = esp_now_send(BROADCAST_ADDR, (uint8_t *) &thisReadings, sizeof(thisReadings));
   
  if (result == ESP_OK) {
    Serial.println("Sent with success");
  }
  else {
    Serial.println("Error sending the data");
  }
  // *****************************
  // END TEMP WIRELESS COMMS
  // *****************************
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
