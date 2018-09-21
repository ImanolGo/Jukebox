/*************************************************************
digitalRead.ino
SparkFun SX1509 I/O Expander Example: digital in (digitalRead)
Jim Lindblom @ SparkFun Electronics
Original Creation Date: September 21, 2015
https://github.com/sparkfun/SparkFun_SX1509_Arduino_Library

This example demonstrates the SX1509's digitalRead
functionality. A pin can either be set as an INPUT or
INPUT_PULLUP. We'll attach an active-low button to an 
INPUT_PULLUP input, then whenever the button read's LOW, we'll
read the state of another INPUT pin.

After uploading the sketch, open your serial monitor and set 
it to 9600 baud.

Hardware Hookup:
  SX1509 Breakout ------ Arduino -------- Breadboard
        GND -------------- GND
        3V3 -------------- 3.3V
      SDA ------------ SDA (A4)
      SCL ------------ SCL (A5)
      0 ---------------------------------]BTN[----GND
      8 -----------------------------Jumper (GND or 3.3V)

Development environment specifics:
  IDE: Arduino 1.6.5
  Hardware Platform: Arduino Uno
  SX1509 Breakout Version: v2.0

This code is beerware; if you see me (or any other SparkFun 
employee) at the local, and you've found our code helpful, 
please buy us a round!

Distributed as-is; no warranty is given.
*************************************************************/

#include <Wire.h> // Include the I2C library (required)
#include <SparkFunSX1509.h> // Include SX1509 library

// SX1509 I2C address (set by ADDR1 and ADDR0 (00 by default):
const byte SX1509_ADDRESS = 0x3F;  // SX1509 I2C address
SX1509 io; // Create an SX1509 object to be used throughout

// SX1509 Pins:
const byte SX1509_INPUT_PIN = 15; // Floating or jumpered input

void setup() 
{
  // Serial is used in this example to display the input value
  // of the SX1509_INPUT_PIN input:
  Serial.begin(9600);
  // Call io.begin(<address>) to initialize the SX1509. If it
  // successfully communicates, it'll return 1.
  if (!io.begin(SX1509_ADDRESS))
  {
    Serial.println("Failed to communicate.");
    while (1) ;
  }

  // Use a pull-up resistor on the button's input pin. When 
  // the button is pressed, the pin will be read as LOW:
   io.pinMode(SX1509_INPUT_PIN, INPUT_PULLUP);
}

void loop() 
{
   Serial.println(io.digitalRead(SX1509_INPUT_PIN));
}
