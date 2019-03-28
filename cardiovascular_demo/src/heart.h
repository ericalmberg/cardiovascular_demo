#ifndef HEART
#define HEART

#include "servoPWMSimple.h"
// servo driver requirements
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

extern int freq;

const int right_atrium_bdc = 200;
const int right_atrium_tdc = 650;
const int left_atrium_bdc = 1000;
const int left_atrium_tdc = 550;
const int right_ventricle_bdc = 1000;
const int right_ventricle_tdc = 550;
const int left_ventricle_bdc = 250;
const int left_ventricle_tdc = 700;

// setup servo objects
extern SimpleServo left_atrium;
extern SimpleServo left_ventricle;
extern SimpleServo right_ventricle;
extern SimpleServo right_atrium;
extern int pump_delay;

// initiate the pwm driver chip
extern Adafruit_PWMServoDriver pwm;

void handleAction();

void pump();

void pumpSlow();

void pumpSlow(int pump_delay);


#endif