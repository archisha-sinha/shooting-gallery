#include <Wire.h>
#include <hd44780.h>
#include <hd44780ioClass/hd44780_I2Cexp.h>
#include <String.h>

const int col = 20;
const int row = 4;

hd44780_I2Cexp lcd;

void lcd_print_text(char* str, int line, int start_pix){
  lcd.setCursor(start_pix, line);
  lcd.print(str);
}

void setup () {
  int err_status;
  err_status = lcd.begin(col, row);
  if(err_status) {
    hd44780::fatalError(err_status);
  }
  lcd.lineWrap();
}
char str[100];
void loop() {
  lcd.setCursor(3,0); //Start at character 4 on line 0
  lcd.print("ZOMBIE ");
  delay(500);
  lcd.setCursor(11,0); //Start at character 4 on line 0
  lcd.print("SLAYER");
  delay(2000);

  lcd.setCursor(0, 2);
  lcd.print("INSERT COIN TO PLAY");
  delay(2000);

  lcd.clear();
  delay(2000);
  
  lcd.setCursor(0,0);
  lcd.print("HIGH SCORE   20");
  delay(1000);
  lcd.setCursor(0,1);
  int data = analogRead(A3);
  sprintf(str, "LAST SCORE   %d", data);
  lcd.print(str);
  delay(1000);
  lcd.setCursor(3, 2);
  lcd.print("ZOMBIE SLAYER!"); 
  lcd.setCursor(5, 3);
  lcd.print("PLAY NOW!");
  delay(2000);
  lcd.clear();
  delay(2000);
}
