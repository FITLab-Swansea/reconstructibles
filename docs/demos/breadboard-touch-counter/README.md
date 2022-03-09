# Touch Counter Example Application w/ Breadboard

TODO: Add link to video

## Video Transcript
(still image below)

This is a demonstration of an example application running on two devices, with hardware wired into breadboards.
The purpose of this demo is to show how all of the key hardware and software systems of ReConstructibles can be combined together, including the display, touch sensing, and wireless and wired communication mechanisms.

Each device is keeping track of how many touch events it and its neighbor have received.
When the touch sensor, this tin foil pad, registers a touch event, the device updates its display with the proper count.
The device also sends this data to the other device, which updates the corresponding number on their own display.
Thus, the two devices keep their counts in sync with each other as touch events are received.

In this example, the devices are sharing their data wirelessly via the ESP-NOW comunication protocol, sending touch counts to the MAC address of their neighboring device.
The demo could be run again with identical results using the Serial communication protocol, through the red and yellow wires here.

![Image of Video Demo](./breadboard-touch-count-demo.png)