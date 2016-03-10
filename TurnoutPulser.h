/*
	TurnoutPulser - a small library for Arduino to briefly trigger a turnout coil.
	
	Released into the public domain.
*/

#ifndef TurnoutPulser_h
#define TurnoutPulser_h
#include <Arduino.h>

class TurnoutPulser
{
	public:
		TurnoutPulser(int pin1, int pin2);
		void begin();
		void set(bool position);
		void loop();
	
	private:
		uint8_t  _pin1;
		uint8_t  _pin2;
		uint16_t _delay;
		bool     _position;
		uint32_t _drive_until;
};

#endif
