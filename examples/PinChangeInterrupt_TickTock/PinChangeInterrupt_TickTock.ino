/*
 Copyright (c) 2014 NicoHood
 See the readme for credit to other people.

 PinChangeInterrupt_TickTock
 Demonstrates how to use the library

 Connect a button/cable to pin 10/11 and ground.
 The value printed on the serial port will increase if pin 10 is rising and decrease if pin 11 is falling.

 PCINT is useful if you are running out of normal INTs or if you are using HoodLoader2.
 PCINT has some delay because of the pin determination overhead.
 Dont use Serial or delay inside the interrupt!
 Keep in mind that this PCINT is not compatible with SoftSerial (at the moment).

 The following pins are usable for PinChangeInterrupt:
 Arduino Uno: All pins are usable
 Arduino Mega: 10, 11, 12, 13, 50, 51, 52, 53, A8 (62), A9 (63), A10 (64), A11 (65), A12 (66), A13 (67), A14 (68), A15 (69)
 Arduino Leonardo: 8, 9, 10, 11, 14 (MISO), 15 (SCK), 16 (MOSI)
 HoodLoader2: All (broken out 1-7) pins are usable
 Attiny 24/44/84: All pins are usable
 Attiny 25/45/85: All pins are usable
 */

#include "PinChangeInterrupt.h"

// see note above to choose the right pin (with a pin change interrupt!) for your Arduino board
#define pinTick 10
#define pinTock 11

volatile long ticktocks = 0;

void setup()
{
  // start serial debug output
  Serial.begin(115200);
  Serial.println(F("Startup"));

  // set pins to input with a pullup
  pinMode(pinTick, INPUT_PULLUP);
  pinMode(pinTock, INPUT_PULLUP);

  // attach the new PinChangeInterrupts and enable event functions below
  attachPinChangeInterrupt(digitalPinToPinChangeInterrupt(pinTick), tick, RISING);
  attachPinChangeInterrupt(digitalPinToPinChangeInterrupt(pinTock), tock, FALLING);
}

void loop() {
  // integer to count the number of prints
  static int i = 0;
  delay(1000);

  // print values
  Serial.print(i, DEC);
  Serial.print(" ");
  Serial.println(ticktocks);

  // abort if we printed 100 times
  if (i >= 100) {
    detachPinChangeInterrupt(digitalPinToPinChangeInterrupt(pinTick));
    detachPinChangeInterrupt(digitalPinToPinChangeInterrupt(pinTock));
  }
  else
    i++;
}

void tick(void) {
  // increase value
  ticktocks++;
}

void tock(void) {
  // decrease value
  ticktocks--;
}