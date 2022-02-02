#include "CapSensor.h"

CapSensor cs_33_32 = CapSensor(33, 32);

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  long start = millis();
  long total = cs_33_32.capSensor(30);
  Serial.print(millis() - start);
  Serial.print("\t");
  Serial.println(total);

  delay(10);
}
