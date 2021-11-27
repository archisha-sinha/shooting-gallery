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
#define START_BUTTON 8 //B1
#define ESTOP_BUTTON 9 //B2
 
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

int standby_turn_flag = 0;
int standby_turn_time = 0;
int mode_select_time = 0;

// Initialize all classes
MCP23017 mcp = MCP23017(MCP_ADDR);
Ping ping(13);
LCD lcd(20, 4);

ADS1115 ads1115_1 = ADS1115(ADS1115_I2C_ADDR_GND);
ADS1115 ads1115_2 = ADS1115(ADS1115_I2C_ADDR_VDD);

Target target1(3, ADS1115_MUX_AIN0_GND, &ads1115_1, 3000);
Target target2(5, ADS1115_MUX_AIN1_GND, &ads1115_1, 3000);
Target target3(6, ADS1115_MUX_AIN2_GND, &ads1115_1, 3000);
Target target4(9, ADS1115_MUX_AIN3_GND, &ads1115_1, 3000);
Target target5(10, ADS1115_MUX_AIN0_GND, &ads1115_2, 3000);
Target target6(11, ADS1115_MUX_AIN1_GND, &ads1115_2, 3000);

Photoresistor coin_photo;

/***** F U N C T I O N S   D E F I N I T I O N S *****/
void mcp_init(void);
bool is_estop_pressed(void);
bool is_start_pressed(void);
int check_mode(void);

/***** M A I N *****/
void setup() {
  Serial.begin(9600);

  mcp_init();
  lcd.lcd_init();
  ping.ping_init();

  ads1115_1.reset();
  ads1115_1.setDeviceMode(ADS1115_MODE_SINGLE);
  ads1115_1.setDataRate(ADS1115_DR_250_SPS);
  ads1115_1.setPga(ADS1115_PGA_4_096);

  ads1115_2.reset();
  ads1115_2.setDeviceMode(ADS1115_MODE_SINGLE);
  ads1115_2.setDataRate(ADS1115_DR_250_SPS);
  ads1115_2.setPga(ADS1115_PGA_4_096);

  coin_photo.initPhotoresistor(ADS1115_MUX_AIN2_GND, &ads1115_2, 3000);
  
  target1.init_target();
  target2.init_target();
  target3.init_target();
  target4.init_target();
  target5.init_target();
  target6.init_target();
  
  target1.flip_backward();
  target2.flip_backward();
  target3.flip_backward();
  target4.flip_backward();
  target5.flip_backward();
  target6.flip_backward();
}

void loop() {
  if(is_estop_pressed()) {
    curr_mode = emergency_stop;
  }
  
  switch(curr_state){
    case idle:
//      lcd.start_screen();
      if(!standby_turn_flag) {
        target1.flip_forward();
        target2.flip_forward();
        target3.flip_forward();
        target4.flip_forward();
        target5.flip_forward();
        target6.flip_forward();
        standby_turn_flag = 1;
        standby_turn_time = millis();
      } else if(standby_turn_flag && (millis() - standby_turn_time >= 10000)) {
        target1.flip_backward();
        target2.flip_backward();
        target3.flip_backward();
        target4.flip_backward();
        target5.flip_backward();
        target6.flip_backward();
        standby_turn_flag = 0;
      }

      if(coin_photo.readADS1115() < 2700) 
      {
        target1.flip_backward();
        target2.flip_backward();
        target3.flip_backward();
        target4.flip_backward();
        target5.flip_backward();
        target6.flip_backward();
        standby_turn_flag = 0;
        
        curr_state = mode_select;
        mode_select_time = millis();
      } else {
        curr_state = idle;
      }
      break;
      
    case mode_select:
      if(millis() - mode_select_time >= 10000) {
        curr_state = set_distance;
      } else {
        curr_mode = check_mode();
  //      lcd.mode_select_screen(curr_mode);
  
        if(is_start_pressed()) {
          curr_state = set_distance;
        } else {
          curr_state = mode_select;
        }
      }
      break;
      
    case set_distance:
      bool distance_status = ping.is_distance_good(mode_target_forward_time[curr_mode]);
      lcd.distance_set_screen(curr_mode, distance_status);
      
      if (distance_status){
        curr_state = play;
      } else {
        curr_state = set_distance;
      }
      break;
      
    case play:
      break;
      
    case end_game:
      
      break;
      
    case emergency_stop:
      curr_state = emergency_stop;
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

//void target_led_on(uint8_t binary_targets) {
//  mcp.writeRegister(MCP23017Register::GPIO_A, binary_targets);
//  //set flag for each led turned on
//  //call target_led_off after time has passed based on flag
//}

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
