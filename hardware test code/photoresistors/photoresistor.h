#ifndef PHOTO_H
#define PHOTO_H

#include "Arduino.h"

#define PHOTO_HIT 610
#define PHOTO_ACTIVE true
#define PHOTO_UNACTIVE false
class Photoresistor
{
	public:
		Photoresistor(int pin);
		void setPhotoresistorState(bool PhotoresistorState);
		bool getPhotoresistorState();
		bool getPhotoresistorHitStatus();
		
	private:
		int pin;
		int pinVal;
		bool Photoresistor_active;
		bool Photoresistor_hit;
};


#endif