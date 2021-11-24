/*
File: target.h
Description: Library for running individual targets
** Use with arduino
*/
#include "target.h"
#include "Arduino.h"

Target::Target(int pin)
{
  servo_pin = pin;
  turn_time_millis = 0;
  flipped_forward = false;
}

void Target::init_target(void)
{
  servo.attach(servo_pin);
  servo.write(0);
}

void Target::flip_forward(void)
{
  servo.write(180);
  turn_time_millis = millis();
  flipped_forward = true;
}

void Target::flip_backward(void)
{
  servo.write(0);
  flipped_forward = false;
}

bool Target::turn_time_elapsed(unsigned long des_delay)
{
  if((millis()-turn_time_millis) >= des_delay) {
    return true;
  } else {
    return false;
  }
  
}

bool Target::is_flipped_forward(void)
{
  return flipped_forward;
}
