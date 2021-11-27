#include "photoresistor.h"
#include "ADS1115-Driver.h"
#include "Arduino.h"

Photoresistor::Photoresistor()
{
	pinVal = ADS_OFFSET;
	Photoresistor_Active = false;
}

void Photoresistor::initPhotoresistor(uint8_t pin, ADS1115 *ad, int ads_active)
{
	ads_pin = pin;
  ads1115 = ad;
  high_voltage = ads_active;
}

//Pass either Photoresistor_ACTIVE or Photoresistor_UNACTIVE
void Photoresistor::setPhotoresistorState(bool PhotoresistorState)
{
		Photoresistor_Active = PhotoresistorState;
}

bool Photoresistor::getPhotoresistorState()
{
	return Photoresistor_Active;
}

bool Photoresistor::getPhotoresistorLitStatus()
{
	if(!Photoresistor_Active) return false;  
  
	if(pinVal >= high_voltage)
	{
		Photoresistor_Active = PHOTO_UNACTIVE;
		return true;
	} 
	else 
	{
		return false;
	}
}

uint16_t Photoresistor::readADS1115(void)
{
  ads1115->setMultiplexer(ads_pin);
  ads1115->startSingleConvertion();

  delayMicroseconds(25); // The ADS1115 needs to wake up from sleep mode and usually it takes 25 uS to do that
  
  while (ads1115->getOperationalStatus() == 0);
  pinVal = ads1115->readConvertedValue();
  if(pinVal > 4096) pinVal = ADS_OFFSET;
  return pinVal;
}
