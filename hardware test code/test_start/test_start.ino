#include <Wire.h>
#include <MCP23017.h>
#include <String.h>

#define MCP23017_addr 0x20
MCP23017 mcp = MCP23017(MCP23017_addr);

uint8_t gpio_read = 0;
#define START_VAL 0x01
#define E_STOP_VAL 0x02

int ad_read = 0;
#define EASY_RANGE 500
#define HARD_RANGE 1023

const int trig_echo = 13;
long duration;
int distanceInch;

int state = 0;

void setup() {
  Wire.begin();
  Serial.begin(9600);
  
  mcp.init();
  mcp.portMode(MCP23017Port::A, 1);
  mcp.portMode(MCP23017Port::B, 0x00);

  mcp.writeRegister(MCP23017Register::GPIO_A, 0x00);
  mcp.writeRegister(MCP23017Register::GPIO_B, 0x00);
  mcp.writeRegister(MCP23017Register::IPOL_B, 0x00); //set polarity of port B

  pinMode(trig_echo, OUTPUT);
}
char str[100];
void loop() {
  // put your main code here, to run repeatedly:
  switch(state) {
    case 0:
      if((mcp.readPort(MCP23017Port::B) & E_STOP_VAL) == E_STOP_VAL) {
        Serial.println("EMERGENCY STOP");
        state = 4;
      } else if ((mcp.readPort(MCP23017Port::B) & START_VAL) == START_VAL){
        Serial.println("Coin detected");
        state = 1;
      }
      break;
    case 1:
      if((mcp.readPort(MCP23017Port::B) & E_STOP_VAL) == E_STOP_VAL) {
        Serial.println("EMERGENCY STOP");
        state = 4;
      } else{
        if(analogRead(A0) <= EASY_RANGE) {
          Serial.println("Easy mode");
        } else if (analogRead(A0) > EASY_RANGE && analogRead(A0) <= HARD_RANGE) {
          Serial.println("Hard mode");
        }
        if ((mcp.readPort(MCP23017Port::B) & START_VAL) == START_VAL) {
          Serial.println("Mode selected");
          state = 2;
        }
      }
      break;  
    case 2:
      if((mcp.readPort(MCP23017Port::B) & E_STOP_VAL) == E_STOP_VAL) {
        Serial.println("EMERGENCY STOP");
        state = 4;
      } else {
        pinMode(trig_echo, OUTPUT);
        digitalWrite(trig_echo, LOW);
        delayMicroseconds(2);
        digitalWrite(trig_echo, HIGH);
        delayMicroseconds(10);
        digitalWrite(trig_echo, LOW);
        pinMode(trig_echo, INPUT);
        duration = pulseIn(trig_echo, HIGH);
        distanceInch = duration*0.0133/2;
        Serial.print("Distance = ");
        Serial.print(distanceInch);
        if(distanceInch < 24){
          Serial.println(":   Too close! Back up to play!!!");
        } else {
          Serial.println(":   Keep it up!");
          Serial.println("Starting game");
          state = 3;
        }
      }
      break;
    case 3:
      if((mcp.readPort(MCP23017Port::B) & E_STOP_VAL) == E_STOP_VAL){
        Serial.println("EMERGENCY STOP");
        state = 4;
      } else {
        Serial.println("PLAYING");
      }
      break;
    case 4:
      Serial.println("GAME STOPPED, RESET TO FIX");
      break;
  }
  delay(500);
}
