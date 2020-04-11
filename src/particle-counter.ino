/*
 * Project particle-counter
 * Description:
 *  Firmware for a Particle Argon to interact with a button, Grove Chainable LED, and
 *  TM1637 4-Digit Display from Grove. The button is a clicker which indicates press on
 *  the LED cycling through hues for each press and incrementing the count available on
 *  the 4-Digit Display.
 * 
 * Author:
 *  Greyson and Jeff Carouth
 */
#include "Grove_ChainableLED.h"
#include "Grove_4Digit_Display.h"

int pinButton = D2;

ChainableLED leds(A4, A5, 1);
TM1637 tm1637(D4, D5);

int pushCount = 0;
int currentState = 0;
int lastState = 0;

void setup()
{
  pinMode(pinButton, INPUT);

  leds.init();
  leds.setColorHSB(0, 0.0, 0.0, 0.0);

  tm1637.init();
  tm1637.set(BRIGHT_TYPICAL);
  tm1637.point(POINT_OFF);
  tm1637.display(0, 0);
  tm1637.display(1, 0);
  tm1637.display(2, 0);
  tm1637.display(3, 0);
}

void loop()
{
  int buttonPressed = digitalRead(pinButton);

  if(buttonPressed) 
  {
    currentState = 1;
  } 
  else 
  {
    currentState = 0;
  }

  if (currentState != lastState) {
    if(buttonPressed)
    {
      int colorSeed = pushCount % 20;
      double color = 0.05 * colorSeed;

      pushCount++;
      pushCount = pushCount % 10000;

      leds.setColorHSB(0, color, 1.0, 0.5);

      int countCopy = pushCount;

      tm1637.display(3, countCopy % 10);
      countCopy /= 10;
      tm1637.display(2, countCopy % 10);
      countCopy /= 10;
      tm1637.display(1, countCopy % 10);
      countCopy /= 10;
      tm1637.display(0, countCopy % 10);
    }
    else
    {
      leds.setColorHSB(0, 0.0, 0.0, 0.0);
    }

    lastState = currentState;
  }
  
  delay(10);
}