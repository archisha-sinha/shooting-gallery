/*
File: target.h
Description: Library for running individual targets
** Use with arduino
*/
#include "target.h"
#include "Photoresistor.h"
#include "Arduino.h"

// Target constructor
Target::Target(int servoPin, uint8_t pin, ADS1115 *ads, int ads_active, int led_pin)
{
	photo.initPhotoresistor(pin, ads, ads_active); 
  servo_pin = servoPin;
  turn_time_millis = 0;
  flipped_forward = false;
  gpio_led_pin = led_pin;
}

// Initializes target servo to face backward
void Target::init_target(void)
{
  servo.attach(servo_pin);
  servo.write(0);
	photo.setPhotoresistorState(PHOTO_ACTIVE);
  led_on_flag = 0;
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

int Target::get_gpio_led_pin(void) {
  return gpio_led_pin;
}

void Target::set_target_led(int led_status)
{
  led_on_flag = led_status;
  led_on_time = millis();
}

bool Target::led_turn_off_ok(void) {
  if((millis() - led_on_time >= 1000) && led_on_flag) {
    return true;
  }
  else {
    return false;
  }
}
