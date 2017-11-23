/* --------------------------------------------------------------------------------------------------- *
* Khanh Truong - khanhptruong@csu.fullerton.edu
* California State University Fullerton
* Created: Oct 20 2017
*
* Description: Contains tasks for motor to run. Receives direction and distancee/degree as input, converts
*			   to time and power to output to motor.
*
*    bit: [15   ][14-12    ][11-3    ][3-0   ]
* format: [reset][direction][dist/deg][unused]
*
* reset: run normally or reset bot by canceling task and clearing queue
*	bit		function
*	0		run normally
*	1		cease, immediatly stops all operations and empties task queue
*
* direction: set direction to go
*	bit		function
*	00		forward
*	01		reverse
*	10		left
*   11		right
*
* dist/deg: distance to go or degree to turn. Resolution of 1cm/1deg
*	bit				function
*	000000000		0cm/1deg
*	000000001		1cm/1deg
*	...				...
*
* Copyright 2017 if u use dis code u owe me $1,000 ayyyyyy lmao
* --------------------------------------------------------------------------------------------------- */

#ifndef MotorTask_h
#define MotorTask_h

#include "Arduino.h"

class MotorTask{
public:
	MotorTask();
	MotorTask(byte topByte, byte botByte);

	void setTask(byte topByte, byte botByte);
	bool getReset();
	unsigned long getRunTime();
	bool getDIR1();
	byte getPWM1();
	bool getDIR2();
	byte getPWM2();

private:
	void parse(byte topByte, byte botByte);

	bool _reset;
	bool _DIR1;
	byte _PWM1;
	bool _DIR2;
	byte _PWM2;
	unsigned long _runTime;
};

#endif