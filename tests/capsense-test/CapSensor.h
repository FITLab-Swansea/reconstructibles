#include "Arduino.h"

#define IO_REG_TYPE        uint32_t

// Modification of the CapSense Library
// TODO: cite this properly

// Sensor interface
class CapSensor
{
  public:
    CapSensor(uint8_t sendPin, uint8_t receivePin);
    long capSensor(uint8_t samples);
    
  private:
    int error;
    unsigned long  leastTotal;
    unsigned int   loopTimingFactor;
    unsigned long  CS_Timeout_Millis;
    unsigned long  CS_AutocaL_Millis;
    unsigned long  lastCal;
    unsigned long  total;

    uint8_t sPin;
    uint8_t rPin;

    int SenseOneCycle(void);
};
