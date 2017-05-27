/*
 * 
 * I don't know why this code doesn't work. When it reaches the end of the line and detects all zeros
 * it decides that it's time to quit. It will only detect the number of white pixels as zero once it
 * detects all zero once. Then it will run the turning on the spot code to turn 90 degrees anticlockwise
 * in order to try find a line. However, due to the bug, it will never detect the line and will just
 * continue turning. The reason it doesn't work properly is because it returns to the colourCamera()
 * function but doesn't run the camera (I honestly have no idea why), so it never runs it again. If you can figure
 * out why that it happening and fix it, that would be great. The just upload it to GitHub and I'll try
 * add it to the code we have already. 
 * 
 * 
 * EDIT: i think i fixed it... maybe. Feel free to test it and see. Unfortuantely, it will juat do some rather 
 * jerky turns on the spot until it reaches an angle where it can see everything.
 * 
 */

#include <stdio.h>
#include <time.h>
#include "E101.h"

float turn90 = 50; // adjust this value to change how fast it turns for
float turnSleepS = 0;
float turnSleepMs = 700000;
float kp =0.3; // figure out a good value. 0.5 kind of worked
float ki = 0;
float kd = 0;
float sp = 50;
bool endOfLineTestOff = true;
bool debug = false; // set to true to debug


/*int turnAC(){ // Turn 90 degrees anti-clockwise
	set_motor(1,-turn90);
	set_motor(2,turn90);
	sleep1(turnSleepS,turnSleepMs);
	set_motor(1,0);
	set_motor(2,0);
	sleep1(2,0);
	return 0;
}

void turnC(){ // Turn 90 degrees clockwise
	set_motor(1,turn90);
	set_motor(2,-turn90);
	sleep1(turnSleepS,turnSleepMs);
	set_motor(1,0);
	set_motor(2,0);
	return;	
}*/

void motor(int err, int x){
	int speed = 100*err/12880;
	if(x<10 && x>0){
		set_motor(1, 2*sp);
		set_motor(2, sp);
		//sleep1(0,500);
	}
	else if(x==0){
		set_motor(1,0);
		set_motor(2,0);
		set_motor(1,-turn90);
	set_motor(2,turn90);
	/*sleep1(turnSleepS,turnSleepMs);
	set_motor(1,0);
	set_motor(2,0);
	sleep1(2,0);
		//return 0;*/ //For some reason, this code is messing everything up. We dont need it, but it you fix it, our robot might look cooler.
		printf("end\n");
	}
	else if(err>=0){
		set_motor(2,-(sp+speed)); //left motor
		set_motor(1,-(sp-2*speed)); //right motor
	}
	else if(err<0){
		set_motor(2,-(sp+2*speed));
		set_motor(1,-(sp-speed));
	}
	//set_motor(1,0);
	//set_motor(2,0);
	//printf("done\n");
}

int colourCamera(){
	int threshold = 100;
	//printf("Camera Started.");
	while(true){
		take_picture();
		//int sumThreshold = 0;
		int numWhite = 0;
		int whiteBool = 0;
		int error = 0;
		for(int i=1; i<320; i++){ // perhaps we could change the number of pixels it detects in the first quadrant to prevent it detecting the wrong line
			char white = get_pixel(230,i,3);
			if(white>threshold){
				whiteBool = 1;
				numWhite++;
				if(debug){
					set_pixel(230, i, 0, 255, 0);
				}
			}
			else {
				whiteBool = 0;
				if(debug){
					set_pixel(230, i, 255, 0, 0);
				}
			}
			//sumThreshold = sumThreshold+white;
			error = error+whiteBool*(i-160);
			double p_signal = error*kp;
			printf("%d\n", numWhite);
			motor(p_signal, numWhite);
		}
		//threshold = sumThreshold/320;
		if(debug){
			display_picture(0,500000);
		}
	}
return 0;
}

int main(){
	init();
	colourCamera();
}
