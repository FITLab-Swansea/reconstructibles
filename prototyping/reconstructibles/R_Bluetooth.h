// Libraries
#include <esp_now.h>
#include <WiFi.h>

// System Constants
#define RBT_ERROR -1

// Broadcasting Constants
#define D1_MAC_ADDR "24:A1:60:74:E1:14" // D1 connected on cu.usbserial-020D10F5
#define D2_MAC_ADDR "24:A1:60:74:E0:FC" // D2 connected on cu.usbserial-020D0A70
uint8_t d1_broadcastAddress[] = {0x24, 0xA1, 0x60, 0x74, 0xE1, 0x14};
uint8_t d2_broadcastAddress[] = {0x24, 0xA1, 0x60, 0x74, 0xE0, 0xFC};

// - Uncomment ONLY one of the following receiver addresses
//#define RECEIVER_ADDR d1_broadcastAddress
#define RECEIVER_ADDR d2_broadcastAddress
// - TODO: make above an array of valid MAC addresses or dynamically generate

// Bluetooth data packet struct
typedef struct rbt_data_packet {
  uint8_t num_presses;
} rbt_data_packet;

// Bluetooth communication manager interface

// Data
uint8_t incomingNumPresses;
// - Data packets for this device and for incoming transmissions
rbt_data_packet outgoingDataPacket;
rbt_data_packet incomingDataPacket;
esp_now_peer_info_t peerInfo;

// Methods
void rbt_start();
void rbt_sendData(uint8_t d);
// - Callback functions
void rbt_cbOnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status);
void rbt_cbOnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len);
