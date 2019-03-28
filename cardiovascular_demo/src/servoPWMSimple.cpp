#include "servoPWMSimple.h"

int m_servo_id;
uint16_t m_min_boundary_value;
uint16_t m_max_boundary_value;
uint16_t m_range;
float m_min_time;
float m_max_time;
int m_div_per_ms;
int current_position;

SimpleServo::SimpleServo(int servo_id, float min_time, float max_time, int freq)
{
    // capture servo min/max times into object
    m_min_time = min_time;
    m_max_time = max_time;

    // capture servo pin id on shield into object
    m_servo_id = servo_id;

    // calculate how long 1 cycle is based on frequency
    float ms_per_cycle = (1.0/freq) * 1000.0;
    Serial.print("ms_per_cycle = ");
    Serial.println(ms_per_cycle);

    // calculate how many divisions (of total 4096) constitute 1ms at this frequency
    m_div_per_ms = 4096.0 / ms_per_cycle;  // 4096 = default resolution of the Adafruit driver
    Serial.print("divs_per_ms = ");
    Serial.println(m_div_per_ms);

    // setup so that start is not at 0 but equally divided at both start & finishe ends
    m_min_boundary_value = (4096 - (m_div_per_ms * max_time)) / 2;
    Serial.print("m_min_boundary_value = ");
    Serial.println(m_min_boundary_value);
    m_max_boundary_value = m_min_boundary_value + max_time * m_div_per_ms;
    Serial.print("m_max_boundary_value = ");
    Serial.println(m_max_boundary_value);
    m_range = m_max_boundary_value - m_min_boundary_value;
    Serial.print("m_range = ");
    Serial.println(m_range);
}

void SimpleServo::move(Adafruit_PWMServoDriver* pwm, int position)
{
    int pulse_width = map(position, 0, 1023, 0, m_range);
    pwm->setPWM(m_servo_id, m_min_boundary_value, m_min_boundary_value + pulse_width);
    Serial.print("Commanded setting: ");
    Serial.println(position);
    Serial.print("pwm.setPWM(");
    Serial.print(m_servo_id);
    Serial.print(",");
    Serial.print(m_min_boundary_value);
    Serial.print(",");
    Serial.print(m_min_boundary_value + pulse_width);
    Serial.println(");");
}