# TinyPICO Setup

Follow these instructions for setting up the TinyPICO boards for prototype development.

1. Install the [Arduinio IDE](https://www.arduino.cc/en/software)
1. Download and install ESP32 libraries for working with TinyPico
    1. Navigate to Arduino > Preferences
    1. Input `https://dl.espressif.com/dl/package_esp32_index.json` under "Additional Boards Manager URLs"
    1. Click "OK"
    1. Navigate to Tools > Board > Boards Manager
    1. Search "esp32" and install the esp32 library by Espressif Systems 
        - This project used v1.0.6 at time of writing this guide, but the latest version should be fine
    1. Navigate to Tools > Manage Libraries
    1. Search "TinyPico" and install the "TinyPICO Helper Library" by UnexpectedMaker
        - This project used v1.4.0 at time of writing this guide, but the latest version should be fine
    1. Close the Library Manager
1. Connect TinyPico board to computer via MicroUSB cable
1. Select the TinyPico Board and port
    1. Select Tools > Board > ESP32 Arduino > TinyPico
    1. Select Tools > Port > [USB serial device name]