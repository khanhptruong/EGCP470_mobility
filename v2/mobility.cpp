/* --------------------------------------------------------------------------------------------------- *
* Khanh Truong - khanhptruong@csu.fullerton.edu
* California State University Fullerton
* Created: Sept 29, 2017
* Last Modified: Oct, 20 2017
*
* Description: This arduino program acts as an intermediary between a motorcontroller and "brain".
* The brain sends 24bit tasks detailing directions, speed, and how long to run said task. This program
* stores the tasks in a queue and executes them sequentially. Upon receiveing a CEASE task, the program
* stops all current operations, purges all tasks from the queue, and waits for further tasks.
*
* Copyright 2017 if u use dis code u owe me $1,000 ayyyyyy lmao
* --------------------------------------------------------------------------------------------------- */

// 0xAF.50.64 = 0b10101111.01010000.01100100 = char �Pd

#include <QueueList.h>
#include <MotorTask.h>
#include <DMDriver.h>

// pins
#define PWM2 11
#define DIR2 10
#define PWM1 9
#define DIR1 8
// other stuff
#define SIZE_OF_TASK 2 // num of bytes

byte scratchByte[SIZE_OF_TASK];
unsigned long runTime; //milliseconds
QueueList <MotorTask> taskQueue;
MotorTask scratchTask;
MotorTask stopTask(B00000000, B00000000); // task that stops the motors
DMDriver driver(DIR1, PWM1, DIR2, PWM2);

void purgeTasks(){
	while (!taskQueue.isEmpty()){ taskQueue.pop(); }
}

void setup() {
	Serial.begin(9600);
	driver.init();
	runTime = 0; // so that next task is loaded upon first-run
	Serial.println("<Farmbot... ACTIVATED>");
}

void loop() {
	if (Serial.available() >= SIZE_OF_TASK) { // download task from navigation
		Serial.readBytes(scratchByte, SIZE_OF_TASK);
		scratchTask.setTask(scratchByte[0], scratchByte[1]);
		if (scratchTask.getReset()){ // is reset true?
			purgeTasks();
			runTime = 0;
		}
		else{
			taskQueue.push(scratchTask);
		}
	}

	if (millis() >= runTime){ // check if current task is complete
		if (taskQueue.isEmpty()){ taskQueue.push(stopTask); }
		scratchTask = taskQueue.pop();
		runTime = scratchTask.getRunTime();
		runTime += millis(); // offset by current time to get end time
		driver.run(scratchTask.getDIR1(),
				   scratchTask.getPWM1(),
				   scratchTask.getDIR2(),
				   scratchTask.getPWM2());
	}

	
	Serial.print("runTime: ");
	Serial.println(runTime, DEC);
	Serial.print("current time: ");
	Serial.print(millis());
	Serial.println(" ms");
	Serial.println("-");
	delay(3000);
}

