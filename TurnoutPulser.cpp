/*
	TurnoutPulser - a small library for Arduino to briefly trigger a turnout coil.
	
	Released into the public domain.
*/

#include "TurnoutPulser.h"
#include <Arduino.h>

TurnoutPulser::TurnoutPulser(int pin1, int pin2)
:  _pin1(pin1)
,  _pin2(pin2)
,  _position(LOW)
,  _drive_until(0)
,  _delay(250)
{
}

// 
// public methods
// 

void TurnoutPulser::begin()
{
	pinMode(_pin1, OUTPUT);
	pinMode(_pin2, OUTPUT);
}

void TurnoutPulser::set(bool position)
{
	// requested position is same as existing position? and has been driven before? ignore
	if (position == _position && _drive_until > 0)
	{
		// ignore any changes
		return;
	}
	
	// change position
	if (position == LOW)
	{
		digitalWrite(_pin1, HIGH);
	}
	else
	{
		digitalWrite(_pin2, HIGH);
	}
	
	// and remember position
	_position = position;
	
	// and update drive time
	_drive_until = millis() + _delay;
}

void TurnoutPulser::loop()
{
	// drive time has elapsed, so detach now
	if (millis() > _drive_until && _drive_until > 0)
	{
		digitalWrite(_pin1, LOW);
		digitalWrite(_pin2, LOW);
	}
}
