/*
 * Library: Simple PWM driver
 * Description: Library written to create easy to interact with servo objects from the adafruit feather PWM driver
 * Author: Eric Almberg
 * Date: March 2019
 */

#ifndef SERVO_PWM_SIMPLE
#define SERVO_PWM_SIMPLE

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

class SimpleServo 
{
    public:
    int m_servo_id;
    uint16_t m_min_boundary_value;
    uint16_t m_max_boundary_value;
    uint16_t m_range;
    float m_min_time;
    float m_max_time;
    int m_div_per_ms;

    public:
    SimpleServo(int servo_id, float min_time, float max_time, int freq);

    void move(Adafruit_PWMServoDriver *pwm, int position);
};

#endif