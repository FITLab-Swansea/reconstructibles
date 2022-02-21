// Libraries
#include "BluetoothSerial.h" // We will include the Serial Bluetooth header

// System configuration check
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial BT;
