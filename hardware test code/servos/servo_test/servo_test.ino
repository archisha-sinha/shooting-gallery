#include <Servo.h>

struct Target{
  Servo servo;
  int servo_pin;
  unsigned long turn_time_millis = 0;
  int flip_ok = 1;
};
Target target_one;
Target target_two;
Target target_three;
Target target_four;

long randNum;

int time_elapsed(unsigned long target_time, unsigned long des_delay) {
  return ((millis() - target_time) >= des_delay);
}

void target__flip_forward(Target target_to_flip) {
  target_to_flip.flip_ok = 0;
  target_to_flip.servo.write(180);
  target_to_flip.turn_time_millis = millis();
}

void target__flip_back(Target target_to_flip) {
  target_to_flip.flip_ok = 1;
  target_to_flip.servo.write(0);
}

void setup() {
  target_one.servo_pin = 5;
  target_two.servo_pin = 6;
  target_three.servo_pin = 9;
  target_four.servo_pin = 10;

  target_one.servo.attach(target_one.servo_pin);
  target_two.servo.attach(target_two.servo_pin);
  target_three.servo.attach(target_three.servo_pin);
  target_four.servo.attach(target_four.servo_pin);

  target_one.servo.write(0);
  target_two.servo.write(0);
  target_three.servo.write(0);
  target_four.servo.write(0);

  randomSeed(analogRead(0));
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  randNum = random(15);
  Serial.println(randNum);
  if((randNum & 1) && target_one.flip_ok){
    target__flip_forward(target_one);
  } 
  if((randNum>>1 & 1) && target_two.flip_ok) {
    target__flip_forward(target_two);
  } 
  if((randNum>>2 & 1) && target_three.flip_ok) {
    target__flip_forward(target_three);
  } 
  if((randNum>>3 & 1) && target_four.flip_ok) {
    target__flip_forward(target_four);
  }

  delay(1000);
  if(time_elapsed(target_one.turn_time_millis, 2000)) {
    target__flip_back(target_one);
  } 
  if(time_elapsed(target_two.turn_time_millis, 2000)) {
    target__flip_back(target_two);
  } 
  if(time_elapsed(target_three.turn_time_millis, 2000)) {
    target__flip_back(target_three);
  } 
  if(time_elapsed(target_four.turn_time_millis, 2000)) {
    target__flip_back(target_four);
  }
}
