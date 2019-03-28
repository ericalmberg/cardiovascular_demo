#include "heart.h"
#include "display.h"

int freq = 250;
int pump_delay = 1000;

SimpleServo left_atrium(0, 1.0, 2.3, freq);
SimpleServo left_ventricle(1, 1.0, 2.3, freq);
SimpleServo right_ventricle(2, 1.0, 2.3, freq);
SimpleServo right_atrium(3, 1.0, 2.3, freq);

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

void handleAction(){
    if(screen_state == home && touch_quadrant == clear){
        return;
    }
    switch(screen_state)
    {
        case home:
            Serial.println("entering home switch case");
            switch (touch_quadrant)
                {
                case top_left:
                    pump();
                    touch_quadrant = clear;
                    break;
                case bottom_left:
                    pumpSlow();
                    touch_quadrant = clear;
                    break;
                case top_right:
                    screen_state = pumping;
                    pump_delay = 1000;
                    touch_quadrant = clear;
                    break;
                case bottom_right:
                    screen_state = slow_pumping;
                    pump_delay = 500;
                    touch_quadrant = clear;
                    break;
                default:
                    break;
            }
            break;
        case pumping:
            switch (touch_quadrant)
            {
                case top_left:
                    screen_state = home;
                    touch_quadrant = clear;
                    break;
                case top_right:
                    if (pump_delay > 0)
                    {
                        pump_delay -= 100;
                    }
                    touch_quadrant = clear;
                    break;
                case bottom_right:
                    pump_delay += 100;
                    touch_quadrant = clear;
                    break;
                default:
                    pump();
                    delay(pump_delay);

            }
            break;
        case slow_pumping:
            switch (touch_quadrant)
            {
            case top_left:
                screen_state = home;
                touch_quadrant = clear;
                break;
            case top_right:
                if (pump_delay > 0)
                {
                    pump_delay -= 100;
                }
                touch_quadrant = clear;
                break;
            case bottom_right:
                pump_delay += 100;
                touch_quadrant = clear;
                break;
            default:
                pumpSlow(pump_delay);
            }
            break;
            break;
        default:
            break;
    }
}

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

void pumpSlow(){
    int offset_increment = 5;
    int step_delay_time = 10;
    for(int offset = 0; offset < 450; offset += offset_increment){
        left_atrium.move(&pwm, left_atrium_tdc + offset); // + because tdc > bdc
        right_atrium.move(&pwm, right_atrium_tdc - offset); // - because tdc < bdc
        delay(step_delay_time);
    }
    delay(500);
    for (int offset = 0; offset < 450; offset += offset_increment)
    {
        left_ventricle.move(&pwm, left_ventricle_tdc - offset);
        right_ventricle.move(&pwm, right_ventricle_tdc + offset);
        delay(step_delay_time);
    }
    delay(1000);
    for (int offset = 0; offset < 450; offset += offset_increment)
    {
        left_atrium.move(&pwm, left_atrium_bdc - offset);   
        right_atrium.move(&pwm, right_atrium_bdc + offset);
        delay(step_delay_time);
    }
    delay(1000);
    for (int offset = 0; offset < 450; offset += offset_increment)
    {
        left_ventricle.move(&pwm, left_ventricle_bdc + offset);
        right_ventricle.move(&pwm, right_ventricle_bdc - offset);
        delay(step_delay_time);
    }
    delay(1000);
}

void pumpSlow(int pump_delay)
{
    int offset_increment = 5;
    int step_delay_time = 10;
    for (int offset = 0; offset < 450; offset += offset_increment)
    {
        left_atrium.move(&pwm, left_atrium_tdc + offset);   // + because tdc > bdc
        right_atrium.move(&pwm, right_atrium_tdc - offset); // - because tdc < bdc
        delay(step_delay_time);
    }
    delay(pump_delay);
    for (int offset = 0; offset < 450; offset += offset_increment)
    {
        left_ventricle.move(&pwm, left_ventricle_tdc - offset);
        right_ventricle.move(&pwm, right_ventricle_tdc + offset);
        delay(step_delay_time);
    }
    delay(pump_delay);
    for (int offset = 0; offset < 450; offset += offset_increment)
    {
        left_atrium.move(&pwm, left_atrium_bdc - offset);
        right_atrium.move(&pwm, right_atrium_bdc + offset);
        delay(step_delay_time);
    }
    delay(pump_delay);
    for (int offset = 0; offset < 450; offset += offset_increment)
    {
        left_ventricle.move(&pwm, left_ventricle_bdc + offset);
        right_ventricle.move(&pwm, right_ventricle_bdc - offset);
        delay(step_delay_time);
    }
    delay(pump_delay);
}