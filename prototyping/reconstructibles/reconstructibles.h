/*
 * reconstructibles.h - ReConstructibles Library
 */

// Display Libraries
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library for ST7735
#include <Adafruit_ST7789.h> // Hardware-specific library for ST7789
#include <SPI.h>

// ReConstructibles Libraries
#include "R_CapacitiveSensing.h"  // Capacitive sensing library

// Display Constants
#define TFT_CS    5  // Chip select pin = SS on TinyPico
#define TFT_RST   26 // Or set to -1 and connect to Arduino RESET pin
#define TFT_DC    25 
#define TFT_MOSI 19  // Data out
#define TFT_SCLK 18  // Clock out

#define TFT_WIDTH 240
#define TFT_HEIGHT 240

// Capacitive Sensing Constants
#define NUM_CAP_SENSE_SAMPLES 30

// UART Constants
#define RX0 14
#define TX0 15
#define UART_COMM_BAUD 9600
