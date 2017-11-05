#include "gogu.h"

void gogu_setPinDirection(byte pinNumber, byte pinDirection)
{
  pinMode(pinNumber, pinDirection);
  digitalWrite(pinNumber, LOW); 
}

void gogu_blinkLed(byte ledNumber, byte blinks)
{
  byte i = 0;

  for (i = 0; i<blinks; i++)
  {
    digitalWrite(ledNumber, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(BLINK_PERIOD);                       // wait for a second
    digitalWrite(ledNumber, LOW);    // turn the LED off by making the voltage LOW
    delay(BLINK_PERIOD);                       // wait for a second
  }
}

