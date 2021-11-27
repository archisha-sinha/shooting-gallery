/***** I N C L U D E S *****/
#include <Wire.h>
#include <String.h>
#include <MCP23017.h>
#include "ADS1115-Driver.h"
#include "lcd.h"
#include "photoresistor.h"
#include "ping.h"
#include "target.h"

/***** D E F I N E S *****/
#define MCP_ADDR 0x20 //gpio expander address

//Button pin on gpio expander
#define START_BUTTON 8
#define ESTOP_BUTTON 9

//High value for mode adc ranges
#define EASY_RANGE 500
#define HARD_RANGE 1023

/***** E N U M S *****/
enum Mode
{
  easy = 0, 
  hard
};

Mode curr_mode = easy;

enum States
{
  idle,
  mode_select, 
  set_distance,
  play,
  end_game,
  emergency_stop
};
States curr_state = idle;

/***** V A R I A B L E S *****/
//Private variables
uint8_t gpio_read = 0;

//Arrays for mode specific values, index arrays with curr_mode enum
int mode_target_forward_time[2] = {5000, 3000}; //Time = 5000ms for easy, 3000ms for hard
int mode_player_distance_inch[2] = {12, 24}; //Distance = 12in for easy, 24in for hard

// Initialize all classes
MCP23017 mcp = MCP23017(MCP_ADDR);

LCD lcd(20, 4);

ADS1115 ads1115 = ADS1115(ADS1115_I2C_ADDR_GND);

Target target1(9, ADS1115_MUX_AIN0_GND, &ads1115, 3000);

Ping ping(13);
/***** F U N C T I O N S   D E F I N I T I O N S *****/
void mcp_init(void);
bool is_estop_pressed(void);
bool is_start_pressed(void);
int check_mode(void);

/***** M A I N *****/
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  mcp_init();
  lcd.lcd_init();
  ping.ping_init();

  ads1115.reset();
  ads1115.setDeviceMode(ADS1115_MODE_SINGLE);
  ads1115.setDataRate(ADS1115_DR_250_SPS);
  ads1115.setPga(ADS1115_PGA_4_096);

  target1.init_target();
  target1.flip_backward();
}

void loop() {
  // put your main code here, to run repeatedly:
  switch(curr_state){
    case idle:
      break;
      
    case mode_select:
      break;
      
    case set_distance:
      break;
      
    case play:
      break;
      
    case end_game:
      break;
      
    case emergency_stop:
      break;
  }
}

/***** F U N C T I O N S   D E C L A R A T I O N S *****/
void mcp_init(void)
{
  mcp.init();
  mcp.portMode(MCP23017Port::A, 1);
  mcp.portMode(MCP23017Port::B, 0x00);

  mcp.writeRegister(MCP23017Register::GPIO_A, 0x00);
  mcp.writeRegister(MCP23017Register::GPIO_B, 0x00);
  mcp.writeRegister(MCP23017Register::IPOL_B, 0x00); //set polarity of port B

}

bool is_estop_pressed(void)
{
  return (mcp.digitalRead(ESTOP_BUTTON));
}

bool is_start_pressed(void)
{
  return (mcp.digitalRead(START_BUTTON));
}

int check_mode(void)
{
  int adc_val = analogRead(A0);
  if(adc_val <= EASY_RANGE) {
    curr_mode = easy;
  } else if (adc_val > EASY_RANGE && adc_val <= HARD_RANGE) {
    curr_mode = hard; 
  }
  return curr_mode;
}
