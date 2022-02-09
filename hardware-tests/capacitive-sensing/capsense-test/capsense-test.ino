// Libraries
#include "CapSensor.h"

// Initialize the capacitive sensor
// - resistor is connected between pins 33 and 32
// - tin foil is connected to pin 32 (receivePin)
CapSensor cs_33_32 = CapSensor(33, 32);

#define NUM_SAMPLES 30

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  long start = millis();

  // Read the sensor NUM_SAMPLES times
  long total = cs_33_32.readSensor(NUM_SAMPLES);

  // Print elapsed time
  Serial.print(millis() - start);
  // Print sensor value
  Serial.print("\t");
  Serial.println(total);

  delay(10);
}
