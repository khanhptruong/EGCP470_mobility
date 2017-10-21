#include "Arduino.h"
#include "DMDriver.h"

DMDriver::DMDriver(byte DIR1, byte PWM1, byte DIR2, byte PWM2){
	_DIR1 = DIR1;
	_PWM1 = PWM1;
	_DIR2 = DIR2;
	_PWM2 = PWM2;
}

void DMDriver::init(){
	pinMode(_DIR1, OUTPUT);
	pinMode(_PWM1, OUTPUT);
	pinMode(_DIR2, OUTPUT);
	pinMode(_PWM2, OUTPUT);
}

void DMDriver::run(bool D1, byte P1, bool D2, byte P2){
	if (D1){ digitalWrite(_DIR1, HIGH); }
	else   { digitalWrite(_DIR1, LOW); }
	analogWrite(_PWM1, P1);

	if (D2){ digitalWrite(_DIR2, HIGH); }
	else   { digitalWrite(_DIR2, LOW); }
	analogWrite(_PWM2, P2);
}