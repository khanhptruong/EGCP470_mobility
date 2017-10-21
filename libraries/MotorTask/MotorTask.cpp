#include "Arduino.h"
#include "MotorTask.h"

#define STOP 1

MotorTask::MotorTask(){
	_driveL = STOP;
	_speedL = 0;
	_driveR = STOP;
	_speedL = 0;
	_runTime = 0;
}

MotorTask::MotorTask(byte topByte, byte midByte, byte botByte){
	parse(topByte, midByte, botByte);
}

void MotorTask::setTask(byte topByte, byte midByte, byte botByte){
	parse(topByte, midByte, botByte);
}

void MotorTask::parse(byte topByte, byte midByte, byte botByte){
	_driveL = topByte & B11000000;
	_driveL >>= 6;
	_driveR = topByte & B00110000;
	_driveR >>= 4;

	if (_driveL != STOP) { _speedL = topByte & B00001111; }
	else { _speedL = 0; }

	if (_driveR != STOP) {
		_speedR = midByte & B11110000;
		_speedR >>= 4;
	}
	else { _speedR = 0; }

	_runTime = midByte & B00001111;
	_runTime <<= 8;
	_runTime |= botByte;
	_runTime *= 100; // convert to milliseconds
}

byte MotorTask::getDriveL() { return _driveL; }
byte MotorTask::getSpeedL() { return _speedL; }
byte MotorTask::getDriveR() { return _driveR; }
byte MotorTask::getSpeedR() { return _speedR; }
unsigned long MotorTask::getRunTime() { return _runTime; }