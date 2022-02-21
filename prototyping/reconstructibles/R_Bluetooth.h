// Libraries
#include <esp_now.h>
#include <WiFi.h>

// Broadcasting Constants
#define D1_MAC_ADDR "24:A1:60:74:E1:14" // D1 connected on cu.usbserial-020D10F5
#define D2_MAC_ADDR "24:A1:60:74:E0:FC" // D2 connected on cu.usbserial-020D0A70
uint8_t d1_broadcastAddress[] = {0x24, 0xA1, 0x60, 0x74, 0xE1, 0x14};
uint8_t d2_broadcastAddress[] = {0x24, 0xA1, 0x60, 0x74, 0xE0, 0xFC};
