#include "Arduino.h"
#include "target.h"

int servoPin = 9;
int photoPin = A0;
Target target(servoPin, photoPin);

void setup() {
  Serial.begin(9600);
  target.init_target();
  target.flip_forward();
}

void loop() {
  if(target.is_flipped_forward())
  {
    if(target.turn_time_elapsed(10000)){
      target.flip_backward();
    } else if(target.target_hit()){
      target.flip_backward();
      Serial.println("Hit!");
    }
  } else {
    delay(2000);
    target.flip_forward();
  }
}
