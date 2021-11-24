/*
File: target.h
Description: Library for running individual targets
** Use with arduino
*/
#ifndef _TARGET_H
#define _TARGET_H

#include "Arduino.h"
#include <Servo.h>

class Target
{
  public:
    Target(int pin);
    void init_target(void);
    void flip_forward(void);
    void flip_backward(void);
    bool turn_time_elapsed(unsigned long des_delay);
    bool is_flipped_forward(void);
    
  private:
    Servo servo;
    int servo_pin;
    unsigned long int turn_time_millis;
    bool flipped_forward;
    
};

#endif _TARGET_H
