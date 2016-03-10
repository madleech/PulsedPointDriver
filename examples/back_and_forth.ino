// toggles the position of your turnout every 5 seconds

#include <TurnoutPulser.h>

TurnoutPulser turnout(9, 10); // L9110S is connected to pins 2 and 3

void setup() {
  turnout.begin();
}

void loop() {
  turnout.loop(); // call this every time in loop()
  
  turnout.set(millis() / 5000 % 2); // change the position of the turnout every 5000ms
}