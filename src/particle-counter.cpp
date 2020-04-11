/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "Particle.h"
#line 1 "/Users/jcarouth/projects/personal/particle-counter/src/particle-counter.ino"
/*
 * Project particle-counter
 * Description:
 * Author:
 * Date:
 */
#include "Grove_ChainableLED.h"
#include "Grove_4Digit_Display.h"

void setup();
void loop();
#line 10 "/Users/jcarouth/projects/personal/particle-counter/src/particle-counter.ino"
int pinButton = D2;
int pinLed = D7;

ChainableLED leds(A4, A5, 1);
TM1637 tm1637(D4, D5);

int pushCount = 9990;
int currentState = 0;
int lastState = 0;

void setup()
{
  pinMode(pinButton, INPUT);
  pinMode(pinLed, OUTPUT);

  leds.init();
  leds.setColorHSB(0, 0.0, 0.0, 0.0);

  tm1637.init();
  tm1637.set(BRIGHT_TYPICAL);
  tm1637.point(POINT_OFF);
  tm1637.display(0, 9);
  tm1637.display(1, 9);
  tm1637.display(2, 9);
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

      //digitalWrite(pinLed, HIGH);
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
      //digitalWrite(pinLed, LOW);
      leds.setColorHSB(0, 0.0, 0.0, 0.0);
    }

    lastState = currentState;
  }
  
  delay(10);
}