#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, I2C_1,  leftEncoder,    sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Sensor, I2C_2,  rightEncoder,   sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Motor,  port1,           LFPrimary,     tmotorVex393_HBridge, openLoop, reversed, driveLeft, encoderPort, I2C_2)
#pragma config(Motor,  port2,           LFSecondary,   tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port3,           LMPrimary,     tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port4,           LBSecondary,   tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port5,           LBPrimary,     tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port6,           RBPrimary,     tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port7,           RBSecondary,   tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port8,           RMPrimary,     tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port9,           RFSecondary,   tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port10,          RFPrimary,     tmotorVex393_HBridge, openLoop, reversed, driveRight, encoderPort, I2C_1)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//


#include "Vex_Competition_Includes.c"
#include "Driver Control Functions.h"
#include "Drive Options.h"
#include "Autons/LeftAuton.h"
#include "Autons/RightAuton.h"

/*

*******************************************
        __   ___  ______      ______
      /  /  /  / /  __  \   /   _   \
     /  / /  /  /  /  |_|  /   / |  |
    /  //  /   |  |___    /   /_/  /
   /     /     \___   \  /   ____ /
  /  /|  |   ___   \  | /   /
 /  / |  |   \  \_/  / /   /
/__/  |__|    \_____/ /___/

*******************************************

*/


void pre_auton(){

}

/* Remove comment section for competition

//Task pre-auton. Do Not Edit
void pre_auton(){
	bLCDBacklight = true;
	for(int i = 0; i < 120; i++) {
		clearLCDLine(0);
		displayLCDNumber(0, 1, nAvgBatteryLevel / 1000., 2);
		wait1Msec(250);
  	clearLCDLine(1);
    displayLCDString(1, i % 17, "GO PUSHBOT");
	}
}

*/


//Task auton starts here
task autonomous(){
	leftAuton();//Choose side for Auton
}


//Task usercontrol
task usercontrol(){
	word btn8dLast;
	bool tankTog = false;
	int stick[4] = { 0, 0, 0, 0 };//Array for killing motor whine
	while(true) {

		//Motor-whine killer
		for(int i = 0; i < 4; i++) {//Completly ANNIHALATES annoying motor whine (like a bug!)
			if(fabs(vexRT[i]) > 15)
				stick[i] = vexRT[i];
			else
				stick[i] = 0;
		}

		//Driver-control
		if (vexRT[Btn8D] && !btn8dLast)
			tankTog = !tankTog;
		btn8dLast = vexRT[Btn8D];

		if(tankTog)
			tank(vexRT[Ch3], vexRT[Ch2]);
		else
			arcade(vexRT[Ch2], vexRT[Ch4]); //vroomVroom (usingProperCodingTechnics)
	}
}

//Hey Lennie do you like my amazing coding skilz???
