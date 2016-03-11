// Example of using a button between pin 4 and ground to control a turnout

#include <TurnoutPulser.h>

TurnoutPulser turnout(2, 3); // L9110S is connected to pins 2 and 3
const int button = 4; // button on pin 4

void setup() {
	turnout.begin();
	pinMode(button, INPUT_PULLUP);
}

void loop() {
	turnout.loop(); // call this every time in loop()
	
	turnout.set(digitalRead(button)); // change the position of the turnout to match button
}