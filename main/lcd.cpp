#include "Arduino.h"
#include "lcd.h"
#include <Wire.h>
#include <hd44780.h>                       // main hd44780 header
#include <hd44780ioClass/hd44780_I2Cexp.h> // i2c expander i/o class header

static hd44780_I2Cexp lcd;

LCD::LCD(int col, int row) 
{
  disp_col = col;
  disp_row = row;
}

void LCD::lcd_init(void) 
{
  lcd.begin(disp_col, disp_row);
}

void LCD::clear_screen(void)
{
  lcd.clear();
}

void LCD::start_screen(void) 
{
  lcd.clear();
  //delay(100);
  lcd.setCursor(3, 0);
  lcd.print("ZOMBIE ");
  //delay(500);
  lcd.setCursor(11, 0);
  lcd.print("SLAYER");
  //delay(1000);
  lcd.setCursor(0, 2);
  lcd.print("INSERT COIN TO PLAY");
  //delay(2000);
  //Show high scores for all modes as well
}

void LCD::mode_select_screen(int curr_adc_mode)
{
//  lcd.clear();
  lcd.setCursor(5, 0);
  if(curr_adc_mode == 0){
    lcd.print("EASY Mode");
  } else if(curr_adc_mode == 1) {
    lcd.print("HARD Mode");
  } 
//    else if(curr_adc_mode == 1) {
//    lcd.print("MEDIUM Mode");
//  } else if(curr_adc_mode == 2) {
//    lcd.print("HARD Mode");
//  }
  
  lcd.setCursor(0, 2);
  char str[20];
  sprintf(str, "HIGH SCORE:    %d", mode_high_scores[curr_adc_mode]);
  lcd.print(str);
  lcd.setCursor(0, 3);
  sprintf(str, "LAST SCORE:    %d", mode_last_scores[curr_adc_mode]);
  lcd.print(str);
}

void LCD::distance_set_screen(int curr_adc_mode, bool distance_status)
{
//  lcd.clear();
  lcd.setCursor(0, 0);
    if(curr_adc_mode == 0){
    lcd.print("EASY MODE SELECTED");
  } else if(curr_adc_mode == 1) {
    lcd.print("HARD MODE SELECTED");
  }
//    else if(curr_adc_mode == 1) {
//    lcd.print("MEDIUM MODE SELECTED");
//  } else if(curr_adc_mode == 2) {
//    lcd.print("HARD MODE SELECTED");
//  }
  
  if (!distance_status) {
    lcd.setCursor(5, 2);
    lcd.print("TOO CLOSE");
    lcd.setCursor(5, 3);
    lcd.print("STEP BACK");
  } else{
    lcd.setCursor(3, 2);
    lcd.print("DISTANCE GOOD");
    lcd.setCursor(3, 3);
    lcd.print("STARTING GAME");
  }
}

void LCD::game_play_screen(int time_left, int curr_score)
{
//  lcd.clear();
  char str[20];
  sprintf(str, "Time Remaining: %d", time_left);
  lcd.setCursor(0, 0);
  lcd.print(str);

  sprintf(str, "Kills: %d", curr_score);
  lcd.setCursor(0, 2);
  lcd.print(str);
}

void LCD::end_game_screen(int curr_score)
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Time Remaining: 0");
  
  char str[20];
  lcd.setCursor(0, 2);
  sprintf(str, "Kills: %d", curr_score);
  lcd.print(str);

  delay(500);
  lcd.setCursor(5, 3);
  lcd.print("GAME OVER");
  delay(1000);
}

void LCD::post_game_screen(int curr_score, int curr_adc_mode)
{
  lcd.clear();
  lcd.setCursor(5, 0);
  lcd.print("GAME OVER");

  delay(500);

  char str[30];
  lcd.setCursor(0, 2);
  sprintf(str, "%d Zombies Killed", curr_score);
  lcd.print(str);

  mode_last_scores[curr_adc_mode] = curr_score;
  
  if(curr_score > mode_high_scores[curr_adc_mode]) {
    mode_high_scores[curr_adc_mode] = curr_score;
    lcd.setCursor(0, 3);
    sprintf(str, "NEW HIGH SCORE");
    lcd.print(str);
  } else {
      lcd.setCursor(0, 3);
      sprintf(str, "High score: %d", mode_high_scores[curr_adc_mode]);
      lcd.print(str);
  }
  delay(5000);
}
