#include "Arduino.h"
#include "ping.h"

Ping::Ping(int pin)
{
  trig_echo_pin = pin;
  duration = 0;
  distance_inch = 0;
  prev_distance = 0;
}

void Ping::ping_init(void) 
{
  pinMode(trig_echo_pin, OUTPUT);
}

bool Ping::is_distance_good(int desired_distance)
{
  send_signal();
  calculate_distance();
  if(distance_inch > 100) {
    distance_inch = prev_distance;
  }
  prev_distance = distance_inch;
  Serial.print("Distance = ");
  Serial.print(distance_inch);
  if(distance_inch < desired_distance) return false;
  return true;
}

void Ping::send_signal(void)
{
  pinMode(trig_echo_pin, OUTPUT);
  digitalWrite(trig_echo_pin, LOW);
  delayMicroseconds(2);
  digitalWrite(trig_echo_pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig_echo_pin, LOW);
  pinMode(trig_echo_pin, INPUT);
  duration = pulseIn(trig_echo_pin, HIGH);
}

void Ping::calculate_distance(void)
{
  distance_inch = duration*0.0133/2;
}
