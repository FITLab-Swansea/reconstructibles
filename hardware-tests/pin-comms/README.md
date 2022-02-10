# Pin-Based Communication

Physically connected ReConstructibles need to communicate via wired methods.
This document outlines tests for various pin-based communication protocols.
Set up two [TinyPicos](/docs/setup/hardware/TinyPICO_SETUP.md) before running these tests.

## UART Test

Follow these instructions for enabling UART communication between TinyPICOs with wired connections.

### Setup
1. Connect TinyPICOs to common ground
1. Connect TinyPICO_1 Rx to TinyPICO_2 Tx and vice versa
    - Pin 15 = Tx, Pin 14 = Rx

### Procedure
1. Compile [`pin_uart.ino`](./pin_uart/pin_uart.ino) with `IS_LISTENER` set to `1` and upload to TinyPICO_1
1. Compile [`pin_uart.ino`](./pin_uart/pin_uart.ino) with `IS_LISTENER` set to `0` and upload to TinyPICO_2
    - **Note:** Ensure that the proper USB device is selected (Tools > Port).
1. Open Arduino Serial console for the listener device (TinyPICO_1 or `IS_LISTENER == 1`)
1. View the data received from the sender device

