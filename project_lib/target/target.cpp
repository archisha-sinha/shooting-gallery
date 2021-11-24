/*
File: target.h
Description: Library for running individual targets
** Use with arduino
*/
#include "target.h"

/*
Function: target_init
Description: Initializes all targets with their selected pins and turns all targets to face backwards
*/
void target_init(int servo1_pin, int servo2_pin, int servo3_pin, int servo4_pin, int servo5_pin, int servo6_pin) {
  target_1.servo_pin = servo1_pin;
  target_1.servo.attach(target_1.servo_pin);
  target_1.servo.write(0);
  target_1.turn_time_millis = 0;
  target_1.flipped_forward = 0;

  target_2.servo_pin = servo2_pin;
  target_2.servo.attach(target_2.servo_pin);
  target_2.servo.write(0);
  target_2.turn_time_millis = 0;
  target_2.flipped_forward = 0;

  target_3.servo_pin = servo3_pin;
  target_3.servo.attach(target_3.servo_pin);
  target_3.servo.write(0);
  target_3.turn_time_millis = 0;
  target_3.flipped_forward = 0;

  target_4.servo_pin = servo4_pin;
  target_4.servo.attach(target_4.servo_pin);
  target_4.servo.write(0);
  target_4.turn_time_millis = 0;
  target_4.flipped_forward = 0;

  target_5.servo_pin = servo5_pin;
  target_5.servo.attach(target_5.servo_pin);
  target_5.servo.write(0);
  target_5.turn_time_millis = 0;
  target_5.flipped_forward = 0;

  target_6.servo_pin = servo6_pin;
  target_6.servo.attach(target_6.servo_pin);
  target_6.servo.write(0);
  target_6.turn_time_millis = 0;
  target_6.flipped_forward = 0;
}

/*
Function: target_flip_forward
Description: Turns specified target to face forward
*/
void target_flip_forward(struct Target t) {
  t.servo.write(180);
  t.turn_time_millis = millis();  //store time when target turned forward
  t.flipped_forward = 1;  //indicate target is facing forward
}

/*
Function: target_flip_backward
Description: Turns specified target to face backwards
*/
void target_flip_backward(struct Target t) {
  t.servo.write(0);
  t.flipped_forward = 0; //indicate target is facing backward
}

/*
Function: target_turn_time_elapsed
Description: Checks if the desired delay has passed since turning target forward
Return: 0: time remaining 1: time complete
*/
int target_turn_time_elapsed(struct Target t, unsigned long des_delay) {
  return ((millis() - t.turn_time_millis) >= des_delay);
}
