#include "Arduino.h"
#include "target.h"
#include "ADS1115-Driver.h"

ADS1115 ads1115 = ADS1115(ADS1115_I2C_ADDR_GND);

int servoPin = 9;
Target target(servoPin, ADS1115_MUX_AIN0_GND, &ads1115, 3000);

void setup() {
  Serial.begin(9600);
  ads1115.reset();
  ads1115.setDeviceMode(ADS1115_MODE_SINGLE);
  ads1115.setDataRate(ADS1115_DR_250_SPS);
  ads1115.setPga(ADS1115_PGA_4_096);
  
  target.init_target();
  target.flip_forward();
}

void loop() {
  Serial.println(target.photo.readADS1115());
  if(target.is_flipped_forward())
  {
    if(target.turn_time_elapsed(5000)){
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
