#include "lcd.h"

LCD disp(20, 4);

void setup() {
//  Wire.begin();
  disp.lcd_init();
}

int flag = 0;
int t = 0;
int c = 10;
int s = 0;
int prev_milli = 0;
void loop() {
  if(flag <= 2) {
    disp.start_screen();
    flag++;  
  }
  if(flag == 3) {
    disp.mode_select_screen(0);
    delay(1500);
    flag++;
  }
  if(flag == 4) {
    disp.mode_select_screen(1);
    delay(1500);
    flag++;
  }
  if(flag == 5) {
    disp.distance_set_screen(1, false);
    delay(1500);
    flag++;
  }
  if(flag == 6) {
    disp.distance_set_screen(1, true);
    delay(1500);
    flag++;
    t = millis();
  }
  if(flag == 7) {
    while(c > 0) {
      if(millis()-prev_milli >= 1000) {
        c--;
        prev_milli = millis();
        disp.game_play_screen(c, s);
        delay(1000);
        if(c%2 == 0) s++;
      }
    }
    flag++;
  }
  if(flag <= 9 && flag > 7) {
    disp.end_game_screen(s);
    delay(1000);
    flag++;
  }
  if(flag == 10) {
    disp.post_game_screen(s, 1);
    flag++;
  }
  if(flag == 11) {
    flag = 0;
  }
}



//#include <Wire.h>
//#include "lcd.h"
//#include <hd44780.h>                       // main hd44780 header
//#include <hd44780ioClass/hd44780_I2Cexp.h> // i2c expander i/o class header
//
//#include <MCP23017.h>
//#include <String.h>
//
//#define MCP23017_addr 0x20
//MCP23017 mcp = MCP23017(MCP23017_addr);
//hd44780_I2Cexp lcd;
//
//const int col = 20;
//const int row = 4;
//
//void lcd_print_text(char* str, int line, int start_pix){
//  lcd.setCursor(start_pix, line);
//  lcd.print(str);
//}
//
//void setup() {
//  Wire.begin();
//  mcp.init();
//  mcp.portMode(MCP23017Port::A, 1);
//  mcp.portMode(MCP23017Port::B, 1);
//
//  mcp.writeRegister(MCP23017Register::GPIO_A, 0x00);
//  mcp.writeRegister(MCP23017Register::GPIO_B, 0x00);
//  
//  int err_status;
//  err_status = lcd.begin(col, row);
//  if(err_status) {
//    hd44780::fatalError(err_status);
//  }
//  lcd.clear();
//}
//
//char str[100];
//void loop() {
//  mcp.writePort(MCP23017Port::A, 0x40);
//  delay(500);
//  mcp.writePort(MCP23017Port::A, 0x00);
//  delay(500);
//  
//  lcd.setCursor(3,0); //Start at character 4 on line 0
//  lcd.print("I<3u ");
//  delay(1000);
//
//  lcd.clear();
//  delay(2000);
//}


////void setup () {
////  int err_status;
////  err_status = lcd.begin(col, row);
////  if(err_status) {
////    hd44780::fatalError(err_status);
////  }
////  lcd.lineWrap();
////}
////char str[100];
////void loop() {
////  lcd.setCursor(3,0); //Start at character 4 on line 0
////  lcd.print("ZOMBIE ");
////  delay(500);
////  lcd.setCursor(11,0); //Start at character 4 on line 0
////  lcd.print("SLAYER");
////  delay(2000);
////
////  lcd.setCursor(0, 2);
////  lcd.print("INSERT COIN TO PLAY");
////  delay(2000);
////
////  lcd.clear();
////  delay(2000);
////  
////  lcd.setCursor(0,0);
////  lcd.print("HIGH SCORE   20");
////  delay(1000);
////  lcd.setCursor(0,1);
////  int data = analogRead(A3);
////  sprintf(str, "LAST SCORE   %d", data);
////  lcd.print(str);
////  delay(1000);
////  lcd.setCursor(3, 2);
////  lcd.print("ZOMBIE SLAYER!"); 
////  lcd.setCursor(5, 3);
////  lcd.print("PLAY NOW!");
////  delay(2000);
////  lcd.clear();
////  delay(2000);
////}
