TurnoutPulser
=============

* Author: Michael Adams (<http://www.michael.net.nz>)
* Copyright (C) 2016 Michael D K Adams.
* Released under the MIT license.

TurnoutPulser is a tiny library to control a Kato or Tomix style two-wire turnout.

Motivation
----------
The motors in these turnouts are a pair of electromagnets wired in parallel to the same two wires. Apply a charge and the electromagnets move the turnout to one position. Reverse the polarity and they move in the opposite direction. Remove the charge and they stay in the position you last set them.

To drive these turnouts, there are a number of approaches you can take, involving rectified AC, capacitive discharge units, DPDT relays, etc. However most of these techniques are quite difficult to interface with an Arduino, a device that likes simple ones and zeros, lows and highs.

Instead I found that by using a L9110S H bridge I could easily use the digital outputs of an Arduino to control my Tomix switches. The L9110S is great because it is very readily available, being found in pairs for $1 including shipping on eBay and Aliexpress.

Managing the state of each H bridge can clutter your code quite quickly, so I quickly wrote up this simple library to look after it for me.

Features
--------
* Super simple API, just a few commands!
* Delivers a carefully timed pulse to the turnout coil; long enough to positively switch the turnout, short enough not to overheat the coil.
* Turns off power to the turnout after a short delay, reducing the power usage of your circuits.
* Non-blocking, so your sketch won't halt while the turnout is pulsed. This makes it easy to continue doing other tasks while driving your turnouts.

Requirements
------------
* An Arduino — http://arduino.cc/
* An H bridge — examples include the L9110S and L298N.

Installation
------------
Download the ZIP archive (https://github.com/madleech/TurnoutPulser/zipball/master), then open the Arduino IDE and choose Sketch > Include Library > Add .ZIP Library... and select your downloaded file.

You should now see in File > Examples > TurnoutPulser entires for the back\_and\_forth example.

Connections
-----------
**L9110S** — From your Arduino, connect two pins to the A-IA and A-IB pins on your L9110S module. Connect GND to ground, and VCC to the RAW pin on your Arduino. Then connect the turnout to the MOTOR A terminals on the board.

**L298N** — The L298N is a bit of an overkill, however it will also work. Connect two pins from your Arduino to the A & B inputs on the L298N module. Connect GND to ground, and VCC to RAW. Make sure the Enable A pin is connected to VCC. Then connect the turnout to the OUT A & B terminals on the board.

Code Examples
-------------
Here is the 'back\_and\_forth' example program, included in the download:

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

Documentation
-------------
**TurnoutPulser(int pin1, int pin2)**
Creates a new TurnoutPulser. Pin1 and 2 are the Arduino pin numbers for the A and B inputs on your H bridge.

**void begin()**
Call this in your `setup` method to setup the turnout. All it does is set pin1 and pin2 to be outputs.

**void loop()**
Call this during your `loop` method. (It doesn't matter how fast or frequently you call it, as long as you call it.) This method is responsible for turning off the juice to your turnout once it has changed position.

**void set(bool position)**
Whenever you want to change the position of your turnout, call this. Pass in TRUE or HIGH and it will switch one direction, pass in FALSE or LOW and it will switch to the other direction. Call it twice with the same position and it won't do anything, because it knows it is already in the right position :) This makes it really easy to drive from digital inputs, just call `set(digitalRead(pin))` and it'll change position whenever the input pin changes.

License
-------
Copyright (c) 2016 Michael D K Adams. http://www.michael.net.nz/

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

