#include <stdio.h>
#include <time.h>
#include "E101.h"

//Deleted integral, we won't need it
float kp = 0.4;
float kd = 0.5;
float sp = 50;
bool debug = false;

void motor(int error, int previousError){
	double signal = turnRatio(error, previousError);
	//THE SIGNAL ISN'T BEING USED YET, MODIFY IT LATER
	
	int speed = 100*err/12880;
	if(err>=0){
	set_motor(2,-(sp+speed)); //left motor
	set_motor(1,-(sp-2*speed)); //right motor
	}
	if(err<0){
	set_motor(2,-(sp+2*speed));
	set_motor(1,-(sp-speed));
	}
}

double turnRatio(int error, int previousError){
	double pSignal = error*kp;
	double dSignal = (error-previousError)*kd;
	double finalSignal = pSignal+dSignal;
	return finalSignal;
}

int colourCamera(){
	//50 was too low, if enough light was shined the robot would've read black lines as 1
	int threshold = 100;
	int x = 0;
	take_picture();
		int sumThreshold = 0;
		int whiteBool = 0;
		int numberWhiteBool = 0;
		for(int i=0; i<320; i++){ 
			// perhaps we could change the number of pixels it detects in the first quadrant to prevent it detecting the wrong line
			// just set it down at the white line in the first quadrant
			char white = get_pixel(230,i,3);
			if(white>threshold){
				whiteBool = 1;
				numWhiteBool++;
				if(debug){
					set_pixel(230, i, 0, 255, 0);
				}
			}
			else{
				whiteBool = 0;
				if(debug){
					set_pixel(230, i, 255, 0, 0);
				}
			}
			error = error+whiteBool*(i-160);
			
			//Checks the area of where it's seeing white and pulls towards that area
			if(numWhiteBool > 0){
				error = error/numWhiteBool;
			}
			
			//motor(error);
			//double p_signal = error*kp; got rid of signal modification here, made a proper method
			//motor(p_signal);
		}
		//threshold = sumThreshold/320;
		if(debug){
			display_picture(0,500000);
		}
		x++;
	}
	return error;
}

void gateOpener(){
	connect_to_server("130.195.6.196", 1024);
	send_to_server("Please0");
	char serverResponse[24];
	recieve_from_server(serverResponse);
	char givenPassKey[24];
	for(int i=0; i<6; i++){
		givenPassKey[i] = serverResponse[i];
	}
	password[6+1] = 0; //so the gate opener knows the pass has been terminated
	
	for(int i=0; i<50; i++){
		printf("DEBUG: THE GATE SHOUL'VE OPENED");
		//delete this whole for loop when the gate opener works
	}
}

boolean checkEndQ3(boolean atEndQ3){
	int threshold = 100;
	int redBool;
	int numberRedBool = 0;
	take_picture();
	for(int i=0; i<320; i++){
		if(get_pixel(230, i, 3) > threshold){
			redBool = 1;
			numberRedBool++;
		}else{
			redBool = 0;
		}
	}
	if(numberRedBool > 200){
		atEndQ3 = true;	
	}
	return atEndQ3;
}

int main(){
	init();
	int error = 0;
	int previousError = 0;
	boolean atEndQ3 = false;
	
	//Loops until it hits red patch
	int previousError = colourCamera();
	gateOpener();
	while(!checkEndQ3){
		error = colourCamera();
		motor(error, previousError);
		atEndQ3 = checkEndQ3(atEndQ3);
	}
}
