/***** I N C L U D E S *****/
#include <Wire.h>
#include <MCP23017.h>
#include <String.h>

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

/***** V A R I A B L E S *****/
//Private variables
uint8_t gpio_read = 0;

// Initialize all classes
MCP23017 mcp = MCP23017(MCP_ADDR);

/***** F U N C T I O N S   D E F I N I T I O N S *****/
void mcp_init(void);
bool is_estop_pressed(void);
bool is_start_pressed(void);
int check_mode(void);

/***** M A I N *****/
void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

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
  } else if (adc_val > EASY_RANGE && adc_val <= HIGH_RANGE) {
    curr_mode = hard; 
  }
  return curr_mode;
}
