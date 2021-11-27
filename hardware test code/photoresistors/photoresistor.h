#ifndef PHOTO_H
#define PHOTO_H

#include "ADS1115-Driver.h"
#include "Arduino.h"

#define ADS_OFFSET 550
#define PHOTO_ACTIVE true
#define PHOTO_UNACTIVE false

class Photoresistor
{
	public:
		Photoresistor();
		void initPhotoresistor(uint8_t pin, ADS1115 *ads1115, int ads_active);
		void setPhotoresistorState(bool PhotoresistorState);
		bool getPhotoresistorState(void);
		bool getPhotoresistorLitStatus(void);
		uint16_t readADS1115(void);
    
	private:
    ADS1115 *ads1115;
    uint8_t ads_pin;
		uint16_t pinVal;
    int high_voltage;
		bool Photoresistor_Active;
};


#endif
