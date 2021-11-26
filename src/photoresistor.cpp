#include "photoresistor.h"
#include "Arduino.h"

Photoresistor::Photoresistor()
{
	pinVal = analogRead(pin);
	Photoresistor_active = false;
	Photoresistor_hit = false;
}

void Photoresistor::setPin(int pin)
{
	pin = pin;
}

//Pass either Photoresistor_ACTIVE or Photoresistor_UNACTIVE
void Photoresistor::setPhotoresistorState(bool PhotoresistorState)
{
		Photoresistor_active = PhotoresistorState;
}

bool Photoresistor::getPhotoresistorState()
{
	return Photoresistor_active;
}

bool Photoresistor::getPhotoresistorHitStatus()
{
	if(Photoresistor_active == PHOTO_UNACTIVE) return false;
	pinVal = analogRead(pin);
	if(pinVal >= PHOTO_HIT)
	{
		Photoresistor_active = PHOTO_ACTIVE;
		return true;
	} 
	else 
	{
		return false;
	}
}