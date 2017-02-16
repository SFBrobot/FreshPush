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


//SPEAKER FUNCTION
task speaker_sound(){
	while(true){
		playSoundFile("pushSound.wav");
		wait1Msec(466);
	}
}


//USER CONTROL FUNCTIONS
void setDriveL(int pwr) {
	motor[LFPrimary] =
		motor[LMPrimary] =
		motor[LBPrimary] =
		motor[LFSecondary] =
		motor[LBSecondary] =
	pwr;
}

void setDriveR(int pwr) {
	motor[RFPrimary] =
		motor[RMPrimary] =
		motor[RBPrimary] =
		motor[RFSecondary] =
		motor[RBSecondary] =
	pwr;
}


//Driver control modes
void arcade(int move, int rot){
	setDriveL(move + rot);
	setDriveR(move - rot);
}

void tank(int lpwr, int rpwr){
	setDriveL(lpwr);
	setDriveR(rpwr);
}


//Auton Functions
void vroomPush(int pwrL, int pwrR, int time){//Goodbye Lennie's amazing code
	setDriveL(pwrL);
	setDriveR(pwrR);
	wait1Msec(time);
	setDriveL(0);
	setDriveR(0);
	wait1Msec(20);
}


//Task pre-auton. Do Not Edit
void pre_auton(){
	bLCDBacklight = true;
	for(int i = 0; i < 120; i = i + 1) {
		clearLCDLine(0);
		displayLCDNumber(0, 1, nAvgBatteryLevel / 1000., 2);
		wait1Msec(250);
  		clearLCDLine(1);
    		displayLCDString(1, i % 17, "GO PUSHBOT");
	}
}

/*

char goPush[10] = { 'G', 'O', ' ', 'P', 'U', 'S', 'H', 'B', 'O', 'T'}

*/



//Task auton starts here
task autonomous(){
	vroomPush(127, 127, 800);
	vroomPush(-127, -127, 500);
}


//Task usercontrol
task usercontrol(){
	startTask (speaker_sound);//Starts speaker
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
		arcade(vexRT[Ch2], vexRT[Ch4]); //vroomVroom (usingProperCodingTechnics)
	}
}
