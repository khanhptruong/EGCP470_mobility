/* --------------------------------------------------------------------------------------------------- *
* Khanh Truong - khanhptruong@csu.fullerton.edu
* California State University Fullerton
* Created: Oct 20 2017
*
* Description: Device driver for Quimat Dual Motor Driver Board. Initializes ports and handles output.
*
* Copyright 2017 if u use dis code u owe me $1,000 ayyyyyy lmao
* --------------------------------------------------------------------------------------------------- */

#ifndef DMDriver_h
#define DMDriver_h

#include "Arduino.h"

class DMDriver{
public:
	DMDriver(byte DIR1, byte PWM1, byte DIR2, byte PWM2);
	void init();
	void run(bool D1, byte P1, bool D2, byte P2);
private:
	byte _DIR1;
	byte _PWM1;
	byte _DIR2;
	byte _PWM2;
};

#endif