#include <Wire.h>
#include <hd44780.h>                       // main hd44780 header
#include <hd44780ioClass/hd44780_I2Cexp.h> // i2c expander i/o class header

#include <MCP23017.h>
#include <String.h>

#define MCP23017_addr 0x20
MCP23017 mcp = MCP23017(MCP23017_addr);
hd44780_I2Cexp lcd;

const int col = 20;
const int row = 4;

void lcd_print_text(char* str, int line, int start_pix){
  lcd.setCursor(start_pix, line);
  lcd.print(str);
}

void setup() {
  Wire.begin();
  mcp.init();
  mcp.portMode(MCP23017Port::A, 1);
  mcp.portMode(MCP23017Port::B, 1);

  mcp.writeRegister(MCP23017Register::GPIO_A, 0x00);
  mcp.writeRegister(MCP23017Register::GPIO_B, 0x00);
  
  int err_status;
  err_status = lcd.begin(col, row);
  if(err_status) {
    hd44780::fatalError(err_status);
  }
  lcd.clear();
}

char str[100];
void loop() {
  mcp.writePort(MCP23017Port::A, 0x40);
  delay(500);
  mcp.writePort(MCP23017Port::A, 0x00);
  delay(500);
  
  lcd.setCursor(3,0); //Start at character 4 on line 0
  lcd.print("I<3u ");
  delay(1000);

  lcd.clear();
  delay(2000);
}

//void setup () {
//  int err_status;
//  err_status = lcd.begin(col, row);
//  if(err_status) {
//    hd44780::fatalError(err_status);
//  }
//  lcd.lineWrap();
//}
//char str[100];
//void loop() {
//  lcd.setCursor(3,0); //Start at character 4 on line 0
//  lcd.print("ZOMBIE ");
//  delay(500);
//  lcd.setCursor(11,0); //Start at character 4 on line 0
//  lcd.print("SLAYER");
//  delay(2000);
//
//  lcd.setCursor(0, 2);
//  lcd.print("INSERT COIN TO PLAY");
//  delay(2000);
//
//  lcd.clear();
//  delay(2000);
//  
//  lcd.setCursor(0,0);
//  lcd.print("HIGH SCORE   20");
//  delay(1000);
//  lcd.setCursor(0,1);
//  int data = analogRead(A3);
//  sprintf(str, "LAST SCORE   %d", data);
//  lcd.print(str);
//  delay(1000);
//  lcd.setCursor(3, 2);
//  lcd.print("ZOMBIE SLAYER!"); 
//  lcd.setCursor(5, 3);
//  lcd.print("PLAY NOW!");
//  delay(2000);
//  lcd.clear();
//  delay(2000);
//}
