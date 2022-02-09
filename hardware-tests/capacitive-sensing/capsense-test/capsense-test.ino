// Libraries
#include "CapSensor.h"

// Initialize the capacitive sensor
CapSensor cs_33_32 = CapSensor(33, 32);
CapSensor cs_21_22 = CapSensor(21, 22);

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  long start = millis();
  long total1 = cs_33_32.capSensor(30);
  long total2 = cs_21_22.capSensor(30);
  Serial.print(millis() - start);
  Serial.print("\t1: ");
  Serial.print(total1);
  if (total1 - 10000 <= 0) {
    Serial.print("\t");
  }
  Serial.print("\t2: ");
  Serial.println(total2);

  delay(10);
}
