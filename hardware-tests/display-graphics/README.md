# Display Tests

This document outlines the procedure for running display tests on the Adafruit 1.3" TFT display and TinyPICO.
Set up the [TinyPico](/docs/setup/hardware/TinyPICO_SETUP.md) and [1.3" Display](/docs/setup/hardware/Adafruit_1.3_Display_SETUP.md) before running these tests.

## Test 1: Adafruit Example Graphics Test
Compile [`graphics-test`](./graphics-test/graphics-test.ino) and upload to the TinyPICO.
- This is the `graphicstest` provided by the Adafruit ST7735 and ST7789 Library (File > Examples > Adafruit ST7735 and ST7789 Library > graphicstest) with modifications to run on the TinyPICO hardware.
- We use connection Option 2, because Option 1 doesn't work on the TinyPICO.

## Test 2: Text Limitations Test
Compile [`display-text-test`](./display-text-test/display-text-test.ino) and upload to the TinyPICO.
- This is based on `graphicstest`, but focuses specifically on the display of text, exploring the effects of font size and text wrapping.
- Experiment with various text sizes, colors, and other parameters.



    