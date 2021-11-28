/***** I N C L U D E S *****/
#include <Wire.h>
#include <String.h>
#include <MCP23017.h>
#include "ADS1115-Driver.h"
#include "lcd.h"
#include "photoresistor.h"
#include "ping.h"
#include "target.h"

/********** D E F I N E S **********/
#define MCP_ADDR 0x20 //gpio expander address

//Button pin on gpio expander
#define START_BUTTON 8 //B1
#define ESTOP_BUTTON 9 //B2
 
//High value for mode adc ranges
#define EASY_RANGE 500
#define HARD_RANGE 1023

/********** E N U M S **********/
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

/********** V A R I A B L E S **********/
/***** Private variables *****/
uint8_t gpio_read = 0;

//Arrays for mode specific values, index arrays with curr_mode enum
int mode_target_forward_time[2] = {5000, 3000}; //Time = 5000ms for easy, 3000ms for hard
int mode_player_distance_inch[2] = {12, 24}; //Distance = 12in for easy, 24in for hard

//Timing flags
int standby_turn_flag = 0;
int standby_turn_time = 0;
int mode_select_time = 0;

//Gameplay timing flags and variables
long randNum = 0;
int curr_score = 0;
int time_left = 0;
int prev_sec = 0;

/***** Initialize all classes *****/
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

/********** F U N C T I O N S   D E F I N I T I O N S **********/
void mcp_init(void);
void target_led_reset(void);
void target_led_on(Target t);
void target_led_off(void);
bool is_estop_pressed(void);
bool is_start_pressed(void);
int check_mode(void);

/***** M A I N **********/
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

  randomSeed(analogRead(A0));
}

void loop() {
  if(is_estop_pressed()) {
    curr_state = emergency_stop;
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
      } 
      else if(standby_turn_flag && (millis() - standby_turn_time >= 10000)) {
        target1.flip_backward();
        target2.flip_backward();
        target3.flip_backward();
        target4.flip_backward();
        target5.flip_backward();
        target6.flip_backward();
        standby_turn_flag = 0;
      }

      if(coin_photo.readADS1115() < 2700) {
        target1.flip_backward();
        target2.flip_backward();
        target3.flip_backward();
        target4.flip_backward();
        target5.flip_backward();
        target6.flip_backward();
        standby_turn_flag = 0;
        
        curr_state = mode_select;
        mode_select_time = millis();
      } 
      else {
        curr_state = idle;
      }
      break;
      
    case mode_select:
      if(millis() - mode_select_time >= 10000) {
        curr_state = set_distance;
      } 
      else {
        curr_mode = check_mode();
  //      lcd.mode_select_screen(curr_mode);
  
        if(is_start_pressed()) {
          curr_state = set_distance;
        } 
        else {
          curr_state = mode_select;
        }
      }
      break;
      
    case set_distance:
      bool distance_status = ping.is_distance_good(mode_target_forward_time[curr_mode]);
//      lcd.distance_set_screen(curr_mode, distance_status);
      
      if (distance_status) {
        time_left = 60;
        prev_sec = millis();
        curr_state = play;
      } 
      else {
        curr_state = set_distance;
      }
      break;
      
    case play:
      if(time_left > 0) {
        target_led_off();
        if(millis() - prev_sec >= 1000) {
          prev_sec = millis();
          time_left--;
          lcd.game_play_screen(time_left, curr_score);
        }
        randNum = random(63);

        if((randNum & 1) && !target1.is_flipped_forward()) {
          target1.flip_forward();  
        } 
        else if(target1.is_flipped_forward()) {
            if(target1.turn_time_elapsed(mode_target_forward_time[curr_mode])) {
              target1.flip_backward();
            } 
            else if(target1.target_hit()) {
              target1.flip_backward();
              target_led_on(target1);
              curr_score++;
            }
        }

        if((randNum>>1 & 1) && !target2.is_flipped_forward()) {
          target2.flip_forward();  
        } 
        else if(target2.is_flipped_forward()) {
            if(target2.turn_time_elapsed(mode_target_forward_time[curr_mode])) {
              target2.flip_backward();
            } 
            else if(target2.target_hit()) {
              target2.flip_backward();
              target_led_on(target1);
              curr_score++;
            }
        }

        if((randNum>>1 & 1) && !target2.is_flipped_forward()) {
          target2.flip_forward();  
        } 
        else if(target2.is_flipped_forward()) {
            if(target2.turn_time_elapsed(mode_target_forward_time[curr_mode])) {
              target2.flip_backward();
            } 
            else if(target2.target_hit()) {
              target2.flip_backward();
              target_led_on(target2);
              curr_score++;
            }
        }

        if((randNum>>2 & 1) && !target3.is_flipped_forward()) {
          target3.flip_forward();  
        } 
        else if(target3.is_flipped_forward()) {
            if(target3.turn_time_elapsed(mode_target_forward_time[curr_mode])) {
              target3.flip_backward();
            } 
            else if(target3.target_hit()) {
              target3.flip_backward();
              target_led_on(target3);
              curr_score++;
            }
        }

        if((randNum>>3 & 1) && !target4.is_flipped_forward()) {
          target4.flip_forward();  
        } 
        else if(target4.is_flipped_forward()) {
            if(target4.turn_time_elapsed(mode_target_forward_time[curr_mode])) {
              target4.flip_backward();
            } 
            else if(target4.target_hit()) {
              target4.flip_backward();
              target_led_on(target4);
              curr_score++;
            }
        }

        if((randNum>>4 & 1) && !target5.is_flipped_forward()) {
          target5.flip_forward();  
        } 
        else if(target5.is_flipped_forward()) {
            if(target5.turn_time_elapsed(mode_target_forward_time[curr_mode])) {
              target5.flip_backward();
            } 
            else if(target5.target_hit()) {
              target5.flip_backward();
              target_led_on(target5);
              curr_score++;
            }
        }

        if((randNum>>5 & 1) && !target6.is_flipped_forward()) {
          target6.flip_forward();  
        } 
        else if(target6.is_flipped_forward()) {
            if(target6.turn_time_elapsed(mode_target_forward_time[curr_mode])) {
              target6.flip_backward();
            } 
            else if(target6.target_hit()) {
              target6.flip_backward();
              target_led_on(target6);
              curr_score++;
            }
        }
      }
      else if(time_left == 0) {
        lcd.end_game_screen(curr_score);
        curr_state = end_game;
      }
      break;
      
    case end_game:
      target_led_reset();
      lcd.post_game_screen(curr_score, curr_mode);
      curr_state = idle;
      break;
      
    case emergency_stop:
      curr_state = emergency_stop;
      break;
  }
}

/********** F U N C T I O N S   D E C L A R A T I O N S **********/
void mcp_init(void)
{
  mcp.init();
  mcp.portMode(MCP23017Port::A, 1);
  mcp.portMode(MCP23017Port::B, 0x00);

  mcp.writeRegister(MCP23017Register::GPIO_A, 0x00);
  mcp.writeRegister(MCP23017Register::GPIO_B, 0x00);
  mcp.writeRegister(MCP23017Register::IPOL_B, 0x00); //set polarity of port B

}

void target_led_reset(void)
{
  mcp.writeRegister(MCP23017Register::GPIO_A, 0x00);
}

void target_led_on(Target t) 
{
  mcp.digitalWrite(t.get_gpio_led_pin(), LED_ON);
  t.set_target_led(LED_ON);
}

void target_led_off(void) 
{
  if(target1.led_turn_off_ok()) {
    mcp.digitalWrite(target1.get_gpio_led_pin(), LED_OFF);
    target1.set_target_led(LED_OFF);
  }
  if(target2.led_turn_off_ok()) {
    mcp.digitalWrite(target2.get_gpio_led_pin(), LED_OFF);
    target2.set_target_led(LED_OFF);
  }
  if(target3.led_turn_off_ok()) {
    mcp.digitalWrite(target3.get_gpio_led_pin(), LED_OFF);
    target3.set_target_led(LED_OFF);
  }
  if(target4.led_turn_off_ok()) {
    mcp.digitalWrite(target4.get_gpio_led_pin(), LED_OFF);
    target4.set_target_led(LED_OFF);
  }
  if(target5.led_turn_off_ok()) {
    mcp.digitalWrite(target5.get_gpio_led_pin(), LED_OFF);
    target5.set_target_led(LED_OFF);
  }
  if(target6.led_turn_off_ok()) {
    mcp.digitalWrite(target6.get_gpio_led_pin(), LED_OFF);
    target6.set_target_led(LED_OFF);
  }
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
