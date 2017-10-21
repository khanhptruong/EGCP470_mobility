/* --------------------------------------------------------------------------------------------------- *
* Khanh Truong - khanhptruong@csu.fullerton.edu
* California State University Fullerton
* Created: Oct 20 2017
*
* Description: Contains tasks for motor to run. Input is 3byte (24bit) serial data.
*
*    bit: [23-22 ][21-20 ][19-16 ][15-12 ][11-0   ]
* format: [driveL][driveR][speedL][speedR][runTime]
* 
* driveL and driveR: controls direction and function
*	bit		function
*	00		cease, immediatly stops all operations and empties task queue
*	01		stop
*	10		forward
*	11		back
*
* speedL and speedL: controls speed of motor, 16 degrees of resolution
*	bit		function
*	0000	stopped
*	...		...
*	1111	fullspeed
*
* runTime: how long to run task, 100ms resolution
*	bit				function
*	0000 0000 0000	0ms
*	0000 0000 0001	100ms
*	0000 0000 0010	200ms
*	...				...
*	1111 1111 1111  409500ms = 6.825min
*
* Copyright 2017 if u use dis code u owe me $1,000 ayyyyyy lmao
* --------------------------------------------------------------------------------------------------- */

#ifndef MotorTask_h
#define MotorTask_h

#include "Arduino.h"

class MotorTask{
public:
	MotorTask();
	MotorTask(byte topByte, byte midByte, byte botByte);

	void setTask(byte topByte, byte midByte, byte botByte);
	byte getDriveL();
	byte getSpeedL();
	byte getDriveR();
	byte getSpeedR();
	unsigned long getRunTime();

private:
	void parse(byte topByte, byte midByte, byte botByte);

	byte _driveL;
	byte _driveR;
	byte _speedL;
	byte _speedR;
	unsigned long _runTime;
};

#endif