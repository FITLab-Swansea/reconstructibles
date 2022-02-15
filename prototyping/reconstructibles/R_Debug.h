/*
 * R_Debug.h - ReConstructibles debug helper
 */

// Helper Functions
#define SerialPrint(x) (Serial.print(F(x)))
#define SerialNewline() (Serial.println())

static bool debugOn = false;

void setDebug(bool debug) 
{
  debugOn = debug;  
}

void setSerial(uint8_t s)
{
  if (debugOn) 
  {
    Serial.begin(s);
  }
}

void debug_SerialPrintln(char* s) 
{
  if (debugOn) 
  {
    Serial.println(F(s)); 
  }
}
