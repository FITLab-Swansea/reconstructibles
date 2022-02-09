/*
  CapSensor.h 
  - Based on CapacitiveSense.h - Capacitive Sensing Library for 'duino / Wiring
  - Modifications made to support TinyPICO hardware
 
  Original Copyright Notice from CapacitiveSense.h:
    https://github.com/PaulStoffregen/CapacitiveSensor
    http://www.pjrc.com/teensy/td_libs_CapacitiveSensor.html
    http://playground.arduino.cc/Main/CapacitiveSensor
    Copyright (c) 2009 Paul Bagder
    Updates for other hardare by Paul Stoffregen, 2010-2016
    vim: set ts=4:
*/

#include "Arduino.h"

// Capacitive sensor interface
class CapSensor
{
  public:
    // Resistor wired between send and receive pins
    // Capacitive sensing pad (e.g. tin foil) wired to receivePin
    CapSensor(uint8_t sendPin, uint8_t receivePin);
    
    // Read sensor value [samples] times and return total
    long readSensor(uint8_t samples);
    
  private:
    int error;

    // Calibration variables
    unsigned long  leastTotal;        // baseline measurement to recognize non-sensed capacitance
    unsigned long  CS_Timeout_Millis; // sensoring reading timeout
    unsigned long  CS_AutocaL_Millis; // calibration timeout
    unsigned long  lastCal;           // track last calibration

    unsigned long  total;             // total of sensor readings

    uint8_t sPin;                     // internal sendPin
    uint8_t rPin;                     // internal receivePin

    int SenseOneCycle(void);          // Complete a single sensor read
};
