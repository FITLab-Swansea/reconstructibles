/*
 * r_mac_address_finder - ReConstructibles Helper Library
 * - Prints device MAC address
 */

#include "WiFi.h"

void setup(){
  Serial.begin(115200);
  WiFi.mode(WIFI_MODE_STA);
  Serial.println(WiFi.macAddress());
}

void loop() {
  // put your main code here, to run repeatedly:

}
