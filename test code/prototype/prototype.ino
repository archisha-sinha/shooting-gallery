#include <Wire.h>
#include <hd44780.h>
#include <hd44780ioClass/hd44780_I2Cexp.h>
#include <String.h>

hd44780_I2Cexp lcd;

const int target_1 = A0;
const int target_2 = A1;
const int led_1 = 1;

int currState = 0;

int curr_score = 0;
int high_score = 0;

int game_time = 0;
int curr_time = 0;
int prev_milli = 0;

char time_left[18];
char score[10];

void setup() {
  // put your setup code here, to run once:
  pinMode(led_1, OUTPUT);
  digitalWrite(led_1, LOW);
  lcd.begin(20, 4);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  switch(currState) {
  case 0:
    lcd.setCursor(3,0); //Start at character 4 on line 0
    lcd.print("ZOMBIE ");
    delay(500);
    lcd.setCursor(11,0); //Start at character 4 on line 0
    lcd.print("SLAYER");
    delay(2000);
    
    
   curr_time = 60;
    prev_milli = millis();
    
    lcd.setCursor(0,0);
    sprintf(time_left, "Time Remaining: %d", curr_time);
    lcd.print(time_left);
    lcd.setCursor(0, 2);
    sprintf(score, "Kills: %d", curr_score);
    lcd.print(score);
    currState = 1;
    break;
  case 1:
    if(curr_time >= 0) {
      if(millis()-prev_milli >= 1000) {
        curr_time--;
        prev_milli = millis();
        lcd.setCursor(0,0);
        sprintf(time_left, "Time Remaining: %d", curr_time);
        lcd.print(time_left);
      }
      Serial.println(analogRead(target_1));
      if(analogRead(target_1) >= 400) {
        curr_score++;
//        digitalWrite(led_1, HIGH);
        lcd.setCursor(0, 2);
        sprintf(score, "Kills: %d", curr_score);
        lcd.print(score);
//        delay(500);
//        digitalWrite(led_1, LOW);
      }
      if(analogRead(target_2) >= 400) {
        curr_score++;
//        digitalWrite(led_2, HIGH);
        lcd.setCursor(0, 2);
        sprintf(score, "Kills: %d", curr_score);
        lcd.print(score);
//        delay(500);
//        digitalWrite(led_1, LOW);
      }
    } else{
      
      currState = 2;
    }
    break;
  case 2:
  lcd.clear();
    lcd.setCursor(0,0);
    sprintf(time_left, "GAME OVER");
    lcd.print(time_left);
    delay(1000);
    lcd.setCursor(0, 1);
    sprintf(score, "%d Zombies Killed", curr_score);
    lcd.print(score);
    char high[14];
    if(curr_score > high_score || high_score == 0){
      high_score = curr_score;
      lcd.setCursor(0, 3);
      sprintf(high, "NEW High score: %d!", high_score);
      lcd.print(high);
    } else {
      lcd.setCursor(0, 3);
      sprintf(high, "High score: %d", high_score);
      lcd.print(high);
    }
    delay(5000);
    break;
  }
}
