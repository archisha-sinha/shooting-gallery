// #include <Servo.h>
//
// struct Target{
//   Servo servo;
//   int servo_pin;
//   unsigned long turn_time_millis = 0;
//   int flip_ok = 1;
// };
// Target target_one;
// Target target_two;
// Target target_three;
// Target target_four;
//
// long randNum;
//
// int time_elapsed(unsigned long target_time, unsigned long des_delay) {
//   return ((millis() - target_time) >= des_delay);
// }
//
// void target__flip_forward(Target target_to_flip) {
//   target_to_flip.flip_ok = 0;
//   target_to_flip.servo.write(180);
//   target_to_flip.turn_time_millis = millis();
// }
//
// void target__flip_back(Target target_to_flip) {
//   target_to_flip.flip_ok = 1;
//   target_to_flip.servo.write(0);
// }
//
// void setup() {
//   target_one.servo_pin = 5;
//   target_two.servo_pin = 6;
//   target_three.servo_pin = 9;
//   target_four.servo_pin = 10;
//
//   target_one.servo.attach(target_one.servo_pin);
//   target_two.servo.attach(target_two.servo_pin);
//   target_three.servo.attach(target_three.servo_pin);
//   target_four.servo.attach(target_four.servo_pin);
//
//   target_one.servo.write(0);
//   target_two.servo.write(0);
//   target_three.servo.write(0);
//   target_four.servo.write(0);
//
//   randomSeed(analogRead(0));
//   Serial.begin(9600);
// }
//
// void loop() {
//   // put your main code here, to run repeatedly:
//   randNum = random(15);
//   Serial.println(randNum);
//   if((randNum & 1) && target_one.flip_ok){
//     target__flip_forward(target_one);
//   }
//   if((randNum>>1 & 1) && target_two.flip_ok) {
//     target__flip_forward(target_two);
//   }
//   if((randNum>>2 & 1) && target_three.flip_ok) {
//     target__flip_forward(target_three);
//   }
//   if((randNum>>3 & 1) && target_four.flip_ok) {
//     target__flip_forward(target_four);
//   }
//
//   delay(1000);
//   if(time_elapsed(target_one.turn_time_millis, 2000)) {
//     target__flip_back(target_one);
//   }
//   if(time_elapsed(target_two.turn_time_millis, 2000)) {
//     target__flip_back(target_two);
//   }
//   if(time_elapsed(target_three.turn_time_millis, 2000)) {
//     target__flip_back(target_three);
//   }
//   if(time_elapsed(target_four.turn_time_millis, 2000)) {
//     target__flip_back(target_four);
//   }
// }
#include <Servo.h>
#include "target.h"

Target target1(3);
Target target2(5);
Target target3(6);
Target target4(9);

void setup() {
  target1.init_target();
  target2.init_target();
  target3.init_target();
  target4.init_target();
  
  randomSeed(analogRead(0));
  Serial.begin(9600);
  delay(1000);
}

long randNum;
void loop() {
  randNum = random(63);
  if((randNum & 1) && !target1.is_flipped_forward()) {
    target1.flip_forward();
    Serial.println("flipped 1 forward");
  }
  if((randNum>>1 & 1) && !target2.is_flipped_forward()) {
    target2.flip_forward();
    Serial.println("flipped 2 forward");
  }
  if((randNum>>2 & 1) && !target3.is_flipped_forward()) {
    target3.flip_forward();
    Serial.println("flipped 3 forward");
  }
  if((randNum>>3 & 1) && !target4.is_flipped_forward()) {
    target4.flip_forward();
    Serial.println("flipped 4 forward");
  }
  
  if(target1.turn_time_elapsed(2000) && target1.is_flipped_forward()) {
    target1.flip_backward();
    Serial.println("flipped 1 backward");
  }
  if(target2.turn_time_elapsed(2000) && target2.is_flipped_forward()) {
    target2.flip_backward();
    Serial.println("flipped 2 backward");
  }
  if(target3.turn_time_elapsed(2000) && target3.is_flipped_forward()) {
    target3.flip_backward();
    Serial.println("flipped 3 backward");
  }
  if(target4.turn_time_elapsed(2000) && target4.is_flipped_forward()) {
    target4.flip_backward();
    Serial.println("flipped 4 backward");
  }
  delay(1000);
}
