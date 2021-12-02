#include <Servo.h>

Servo one;
Servo two;
Servo three;
Servo four;
Servo five;
Servo six;

void setup() {
  // put your setup code here, to run once:
  one.attach(3);
  two.attach(5);
  three.attach(6);
  four.attach(9);
  five.attach(10);
  six.attach(11);

  one.write(0);
  two.write(0);
  three.write(0);
  four.write(0);
  five.write(0);
  six.write(0);
  delay(3000);
  one.write(90);
  two.write(90);
  three.write(90);
  four.write(90);
  five.write(90);
  six.write(90);
  delay(3000);
  one.write(180);
  two.write(180);
  three.write(180);
  four.write(180);
  five.write(180);
  six.write(180);
  delay(5000);
}

void loop() {
  // put your main code here, to run repeatedly:

}
