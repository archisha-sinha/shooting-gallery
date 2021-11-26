//#include <Servo.h>
//#include "photoresistor.h"
//
//Photoresistor photo1(A0);
//Servo servo1;
//
//void setup() {
//  Serial.begin(9600);
//  photo1.setPhotoresistorState(PHOTO_ACTIVE);
//  servo1.attach(9);
//  servo1.write(0);
//}
//
//void loop() {
//  if(photo1.getPhotoresistorHitStatus()){
//    Serial.println("Target Hit");
//    servo1.write(180);
//    delay(2000);
//    servo1.write(0);
//    photo1.setPhotoresistorState(PHOTO_ACTIVE);
//  } else {
//    Serial.println(analogRead(A0));
//  }
//}


void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.println(analogRead(A0));
}

/*
// Photoresistors

void setup() {
  Serial.begin(9600);         
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
}

void loop() {
  if((((float)analogRead(A0)) * 5.f / 1023.f) > 3.f){
    digitalWrite(6, HIGH);
    delay(200);
    digitalWrite(6, LOW);
  }
  else if((((float)analogRead(A2)) * 5.f / 1023.f) > 3.f){
    digitalWrite(5, HIGH);
    delay(200);
    digitalWrite(5, LOW);
    Serial.println(((float)analogRead(A2)) * 5.f / 1023.f);
  }
  else if((((float)analogRead(A3)) * 5.f / 1023.f) > 3.f){
    digitalWrite(4, HIGH);
    delay(200);
    digitalWrite(4, LOW);
  }
  else if((((float)analogRead(A4)) * 5.f / 1023.f) > 3.f){
    digitalWrite(3, HIGH);
    delay(200);
    digitalWrite(3, LOW);
  }
  else if((((float)analogRead(A5)) * 5.f / 1023.f) > 3.f){
    digitalWrite(2, HIGH);
    delay(200);
    digitalWrite(2, LOW);
  }
  Serial.println(((float)analogRead(A0)) * 5.f / 1023.f);
}
*/
