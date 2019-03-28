/*
 * Project: Ramapo Engineering Design Project
 * Description: Mechanical analog of the cardiovascular system
 * Author: Eric Almberg
 * Date: March 2019
 */

#include <Arduino.h>
#include "heart.h"
#include "display.h"

void setup()
{
  Serial.begin(9600);

  // setup the pwm driver chip
  pwm.begin();
  pwm.setPWMFreq(freq);
  Wire.setClock(400000);

  // initialize the servo positions
  left_atrium.move(&pwm, left_atrium_tdc);
  right_atrium.move(&pwm, right_atrium_tdc);
  left_ventricle.move(&pwm, left_ventricle_tdc);
  right_ventricle.move(&pwm, right_ventricle_tdc);
  delay(1000);

  // display setup
  tft.begin();
  tft.setRotation(1);
  touch_quadrant = clear;
  screen_state = home;
  last_screen_state = unknown;

  // touch setup
  Serial.println("FeatherWing TFT");
  if (!ts.begin())
  {
    Serial.println("Couldn't start touchscreen controller");
    while (1)
      ;
  }
  Serial.println("Touchscreen started");
}

void loop()
{
  handleDisplay();
  handleTouch();
  handleAction();
}