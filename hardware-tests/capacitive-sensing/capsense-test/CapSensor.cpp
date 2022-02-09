/*
  CapSensor.cpp
  - Based on CapacitiveSense.cpp - Capacitive Sensing Library for 'duino / Wiring
  - Modifications made to support TinyPICO hardware
 
  Original Copyright Notice from CapacitiveSense.h:
    https://github.com/PaulStoffregen/CapacitiveSensor
    http://www.pjrc.com/teensy/td_libs_CapacitiveSensor.html
    http://playground.arduino.cc/Main/CapacitiveSensor
    Copyright (c) 2009 Paul Bagder
    Updates for other hardare by Paul Stoffregen, 2010-2016
    vim: set ts=4:
*/
#include "CapSensor.h"

/**********************************
 * PUBLIC METHODS
 *********************************/

// CapSense class initializer
// - The resistor should be wired between send and receive pins
// - The capacitive sensing pad (e.g. tin foil) should be wired to receivePin
CapSensor::CapSensor(uint8_t sendPin, uint8_t receivePin)
{
  error = 1;
  
  // Set pin modes
  pinMode(sendPin, OUTPUT);   // sendpin to OUTPUT
  pinMode(receivePin, INPUT); // receivePin to INPUT
  digitalWrite(sendPin, LOW); // start with no signal on sendPin

  // Save send and receive pins internally
  sPin = sendPin;
  rPin = receivePin;

  // Initialize calibration variables
  // - Compute timeout values
  unsigned int loopTimingFactor = 310;
  CS_Timeout_Millis = (2000 * (float)loopTimingFactor * (float)F_CPU) / 16000000;
  CS_AutocaL_Millis = 20000;
  // - Input large value for calibrate baseline
  leastTotal = 0x0FFFFFFFL;
  // - Set millis for start
  lastCal = millis();
}

// Read the capacitive sensor
// - samples = number of times to read capacitive sensor
// - returns total value of sensor across samples
long CapSensor::readSensor(uint8_t samples)
{
  // clear total
  total = 0;
  
  if (samples == 0) return 0;

  // Check error state
  if (error < 0) return -1;

  // Sample sensor
  for (uint8_t i = 0; i < samples; i++) 
  { 
    if (SenseOneCycle() < 0) return -2;   // timeout exceeded
  }

  // Calibrate only if time is greater than CS_AutocaL_Millis and total is less than 10% of baseline
  // this is an attempt to keep from calibrating when the sensor is seeing a "touched" signal
  if ( (millis() - lastCal > CS_AutocaL_Millis) && 
        abs(total  - leastTotal) < (int)(.10 * (float)leastTotal) ) 
  {
    // Reset calibration
    leastTotal = 0x0FFFFFFFL;
    lastCal = millis();
  }

  // Update baseline if needed
  if (total < leastTotal) leastTotal = total;
  // Subtract baseline (non-sensed capacitance) from sensor before returning return
  return(total - leastTotal);
}

/**********************************
 * PRIVATE METHODS
 *********************************/

// Read the sensor one time
// - returns 1 if successful, otherwise returns error
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

  // Increment total, while receive pin is LOW AND total is positive value
  while ( !digitalRead(rPin) && (total < CS_Timeout_Millis) ) 
  { 
    total++;
  }

  // If total exceeds timeout, return error
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
  
  // Increment total while receive pin is HIGH and total is positive
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
