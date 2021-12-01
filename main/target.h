/*
File: target.h
Description: Library for running individual targets
** Use with arduino
*/
#ifndef _TARGET_H
#define _TARGET_H

#include "Arduino.h"
#include "Photoresistor.h"
#include <Servo.h>

#define LED_ON 1
#define LED_OFF 0

class Target
{
  public:
    Photoresistor photo;
    Target(int servoPin, uint8_t pin, ADS1115 *ads, int ads_active, int led_pin);
    void init_target(void);
    void flip_forward(void);
    void flip_backward(void);
    bool turn_time_elapsed(unsigned long des_delay);
    bool is_flipped_forward(void);
		bool target_hit(void);
    int get_gpio_led_pin(void);
    void set_target_led(int led_status);
    bool led_turn_off_ok(unsigned long led_time, unsigned long curr_time);
    
  private:
    Servo servo;
    int servo_pin;
    unsigned long int turn_time_millis;
    bool flipped_forward;
    int gpio_led_pin;
    int led_on_flag;
//    unsigned long led_on_time;
};

#endif _TARGET_H
