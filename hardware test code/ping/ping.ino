#include "ping.h"

Ping ping(13);

void setup() {
  // put your setup code here, to run once:
  ping.ping_init();
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(!ping.is_distance_good(24)) {
    Serial.println(":   Too close! Back up to play!!!");
  } else {
    Serial.println(":   Keep it up!");
    Serial.println("Starting game");
  }
//  Serial.println(ping.is_distance_good(24));
  delay(1000);
}
