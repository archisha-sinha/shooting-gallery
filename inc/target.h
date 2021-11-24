/*
File: target.h
Description: Library for running individual targets
** Use with arduino
*/
#ifndef _TARGET_H
#define _TARGET_H

#include <Arduino.h>
#include <Servo.h>

struct Target{
  Servo servo; //target's specific servo
  int servo_pin;  //pin connected to target's servo
  unsigned long int turn_time_millis; //saves time when target turned forward
  int flipped_forward;  //0: target facing backwards, 1: target facing forward
};

struct Target target_1;
struct Target target_2;
struct Target target_3;
struct Target target_4;
struct Target target_5;
struct Target target_6;

void target_init(int servo1_pin, int servo2_pin, int servo3_pin, int servo4_pin, int servo5_pin, int servo6_pin);
void target_flip_forward(struct Target t);
void target_flip_backward(struct Target t);
int target_turn_time_elapsed(struct Target t, unsigned long des_delay);


#endif _TARGET_H
