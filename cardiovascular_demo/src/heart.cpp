#include "heart.h"

int freq = 250;

SimpleServo left_atrium(0, 1.0, 2.3, freq);
SimpleServo left_ventricle(1, 1.0, 2.3, freq);
SimpleServo right_ventricle(2, 1.0, 2.3, freq);
SimpleServo right_atrium(3, 1.0, 2.3, freq);

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

void pump()
{
    left_atrium.move(&pwm, left_atrium_bdc);
    right_atrium.move(&pwm, right_atrium_bdc);
    delay(150);
    left_ventricle.move(&pwm, left_ventricle_bdc);
    right_ventricle.move(&pwm, right_ventricle_bdc);
    delay(300);
    left_atrium.move(&pwm, left_atrium_tdc);
    right_atrium.move(&pwm, right_atrium_tdc);
    delay(150);
    left_ventricle.move(&pwm, left_ventricle_tdc);
    right_ventricle.move(&pwm, right_ventricle_tdc);
    delay(300);
}

void pump_slow(){

}