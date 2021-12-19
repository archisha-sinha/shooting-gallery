//#include "Arduino.h"
//#include "ADS1115-Driver.h"
//#include "photoresistor.h"
//
//ADS1115 ads1115 = ADS1115(ADS1115_I2C_ADDR_GND);
//Photoresistor photo;

//void setup() {
//  Serial.begin(9600);
//
//  ads1115.reset();
//  ads1115.setDeviceMode(ADS1115_MODE_SINGLE);
//  ads1115.setDataRate(ADS1115_DR_250_SPS);
//  ads1115.setPga(ADS1115_PGA_4_096);
//
//  photo.initPhotoresistor(ADS1115_MUX_AIN0_GND, &ads1115, 3000);
//  photo.setPhotoresistorState(PHOTO_ACTIVE);
//}
//
//void loop(){
//  uint16_t value = photo.readADS1115(); 
//  Serial.print("Values: ");
//  Serial.print("IN 0: ");
//  Serial.print(value);
//
//  if(photo.getPhotoresistorLitStatus()){
//      Serial.print("   Lit");
//      delay(2000);
//      photo.setPhotoresistorState(PHOTO_ACTIVE );
//  }
//  
//  Serial.println("");
//  delay(100);
//}


#include "Arduino.h"

void setup() {
  Serial.begin(9600);
}

void loop(){
  Serial.println(analogRead(A0));
//  if(analogRead(A0) < 200){
//    Serial.print(A0);
//    Serial.println("  blocked");
//  } else {
////    Serial.println("not blocked");
//  }
}
