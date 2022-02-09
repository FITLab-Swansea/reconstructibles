#include "CapSensor.h"

CapSensor::CapSensor(uint8_t sendPin, uint8_t receivePin)
{
  error = 1;
  loopTimingFactor = 310;

  CS_Timeout_Millis = (2000 * (float)loopTimingFactor * (float)F_CPU) / 16000000;
  CS_AutocaL_Millis = 20000;

  pinMode(sendPin, OUTPUT);           // sendpin to OUTPUT
  pinMode(receivePin, INPUT);           // receivePin to INPUT
  digitalWrite(sendPin, LOW);

  sPin = sendPin;
  rPin = receivePin;

  // get pin mapping and port for receive Pin - from digital pin functions in Wiring.c
  leastTotal = 0x0FFFFFFFL;   // input large value for autocalibrate begin
  lastCal = millis();         // set millis for start
}

long CapSensor::capSensor(uint8_t samples)
{
  total = 0;
  if (samples == 0) return 0;
  if (error < 0) return -1;            // bad pin

  // Loop for samples
  for (uint8_t i = 0; i < samples; i++) 
  { 
    if (SenseOneCycle() < 0) return -2;   // variable over timeout
  }

  // only calibrate if time is greater than CS_AutocaL_Millis and total is less than 10% of baseline
  // this is an attempt to keep from calibrating when the sensor is seeing a "touched" signal

  if ( (millis() - lastCal > CS_AutocaL_Millis) && 
        abs(total  - leastTotal) < (int)(.10 * (float)leastTotal) ) 
  {

  leastTotal = 0x0FFFFFFFL;          // reset for "autocalibrate"
  lastCal = millis();
  }

  // routine to subtract baseline (non-sensed capacitance) from sensor return
  if (total < leastTotal) leastTotal = total;                 // set floor value to subtract from sensed value
  return(total - leastTotal);
}

// Private Methods /////////////////////////////////////////////////////////////

int CapSensor::SenseOneCycle(void)
{
  noInterrupts();
  digitalWrite(sPin, LOW);  // Send => LOW
  pinMode(rPin, INPUT);     // Toggle Receive Mode
  pinMode(rPin, OUTPUT);
  digitalWrite(rPin, LOW); // Receive => LOW
  delayMicroseconds(10);
  pinMode(rPin,INPUT);
  digitalWrite(sPin, HIGH);
  interrupts();

  // while receive pin is LOW AND total is positive value
  while ( !digitalRead(rPin) && (total < CS_Timeout_Millis) ) 
  { 
    total++;
  }

  if (total > CS_Timeout_Millis) 
  {
    return -2;
  }

  noInterrupts();
  digitalWrite(rPin, HIGH);
  pinMode(rPin, OUTPUT);
  digitalWrite(rPin, HIGH);
  pinMode(rPin, INPUT);
  digitalWrite(sPin, LOW);
  interrupts();
  
  while (digitalRead(rPin) && (total < CS_Timeout_Millis) ) 
  {
    total++;
  }

  if (total >= CS_Timeout_Millis) 
  {
    return -2;
  } else {
    return 1;
  }
}
