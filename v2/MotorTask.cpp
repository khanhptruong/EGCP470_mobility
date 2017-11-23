#include "Arduino.h"
#include "MotorTask.h"

#define WHEEL_CIRC 79 // wheel circumference in cm
#define RPM 10 // after accounting for gear ratio
#define BOT_CIRC 192 // circumference using distance between wheels as diamterer, in cm

MotorTask::MotorTask(){
	_reset = false;
	_DIR1 = true;
	_PWM1 = 0;
	_DIR2 = true;
	_PWM2 = 0;
	_runTime = 0;
}

MotorTask::MotorTask(byte topByte, byte botByte){
	parse(topByte, botByte);
}

void MotorTask::setTask(byte topByte, byte botByte){ parse(topByte, botByte); }

bool MotorTask::getReset(){ return _reset; }
unsigned long MotorTask::getRunTime(){ return _runTime; }
bool MotorTask::getDIR1(){ return _DIR1; }
byte MotorTask::getPWM1(){ return _PWM1; }
bool MotorTask::getDIR2(){ return _DIR2; }
byte MotorTask::getPWM2(){ return _PWM2; }

void MotorTask::parse(byte topByte, byte botByte){
	int dir, mag;
	_reset = topByte >> 8;
	_PWM1 = 128;
	_PWM2 = 128;

	dir = (topByte & B01100000) >> 3;
	mag = (topByte & B00011111) << 4; // set top 5 bits
	mag = mag | ((botByte & B11110000) >> 4); // set bot 4 bits

	switch (dir){
		case 0:
			_DIR1 = true;
			_DIR2 = true;
			_runTime = (mag * 60) / (WHEEL_CIRC * RPM); // the 60 is 60s = 1min
			_runTime *= 1000; // convert to millisec
			break;
		case 1:
			_DIR1 = false;
			_DIR2 = false;
			_runTime = (mag * 60) / (WHEEL_CIRC * RPM); // the 60 is 60s = 1min
			_runTime *= 1000; // convert to millisec
			break;
		case 2:
			_DIR1 = false;
			_DIR2 = true;
			mag = (BOT_CIRC * mag) / 360; // convert turn degrees into arc length
			_runTime = (mag * 60) / (BOT_CIRC * RPM); // the 60 is 60s = 1min
			_runTime *= 1000; // convert to millisec
			break;
		case 3:
			_DIR1 = true;
			_DIR2 = false;
			mag = (BOT_CIRC * mag) / 360; // convert turn degrees into arc length
			_runTime = (mag * 60) / (BOT_CIRC * RPM); // the 60 is 60s = 1min
			_runTime *= 1000; // convert to millisec
			break;
	}
}