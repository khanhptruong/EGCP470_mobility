#include "Arduino.h"
#include "DMDriver.h"

DMDriver::DMDriver(byte PIN_DIR1, byte PIN_PWM1, byte PIN_DIR2, byte PIN_PWM2){
	_PIN_DIR1 = PIN_DIR1;
	_PIN_PWM1 = PIN_PWM1;
	_PIN_DIR2 = PIN_DIR2;
	_PIN_PWM2 = PIN_PWM2;
}

void DMDriver::init(){
	pinMode(_DIR1, OUTPUT);
	pinMode(_PWM1, OUTPUT);
	pinMode(_DIR2, OUTPUT);
	pinMode(_PWM2, OUTPUT);
}

void DMDriver::run(bool D1, byte P1, bool D2, byte P2){
	if (D1){ digitalWrite(_PIN_DIR1, HIGH); }
	else   { digitalWrite(_PIN_DIR1, LOW); }
	analogWrite(_PIN_PWM1, P1);

	if (D2){ digitalWrite(_PIN_DIR2, HIGH); }
	else   { digitalWrite(_PIN_DIR2, LOW); }
	analogWrite(_PIN_PWM2, P2);
}