/*
File: target.h
Description: Library for running individual targets
** Use with arduino
*/
#include "target.h"
#include "Photoresistor.h"
#include "Arduino.h"

// Target constructor
Target::Target(int servoPin, uint8_t pin, ADS1115 *ads, int ads_active)
{
	photo.initPhotoresistor(pin, ads, ads_active); 
  servo_pin = servoPin;
  turn_time_millis = 0;
  flipped_forward = false;
}

// Initializes target servo to face backward
void Target::init_target(void)
{
  servo.attach(servo_pin);
  servo.write(0);
	photo.setPhotoresistorState(PHOTO_ACTIVE);
}

//Turns target servo to face forward and gets time of turn
void Target::flip_forward(void)
{
  servo.write(180);
  turn_time_millis = millis();
  flipped_forward = true;
	photo.setPhotoresistorState(PHOTO_ACTIVE);
}

//Turns target servo to face forward
void Target::flip_backward(void)
{
  servo.write(0);
  flipped_forward = false;
	photo.setPhotoresistorState(PHOTO_UNACTIVE);
}

//Checks if the desired time has passed after turning the target forward
//Returns: true = time done, false = time remaining
bool Target::turn_time_elapsed(unsigned long des_delay)
{
  if((millis()-turn_time_millis) >= des_delay) {
    return true;
  } else {
    return false;
  }
}

bool Target::target_hit(void)
{
	return photo.getPhotoresistorLitStatus();
}

//Checks if the target is facing flip_forward
//Returns: true: forward, false = backward
bool Target::is_flipped_forward(void)
{
  return flipped_forward;
}
