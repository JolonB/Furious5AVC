#include <stdio.h>
#include <time.h>
#include "E101.h"

//Deleted integral, we won't need it
float kp = 0.4;
float kd = 0.5;
float sp = 50;
bool debug = false;



double turnRatio(int error, int previousError){
	double pSignal = error*kp;
	double dSignal = (error-previousError)*kd;
	double finalSignal = pSignal+dSignal;
	return finalSignal;
}

void motor(int error, int previousError){
	//double signal = turnRatio(error, previousError);
	//THE SIGNAL ISN'T BEING USED YET, MODIFY IT LATER SO THAT IT DOES
	
	int speed = 100*error/12880;
	if(error>=0){
	set_motor(2,-(sp+speed)); //left motor
	set_motor(1,-(sp-2*speed)); //right motor
	}
	if(error<0){
	set_motor(2,-(sp+2*speed));
	set_motor(1,-(sp-speed));
	}
}

int colourCamera(){
	//50 was too low, if enough light was shined the robot would've read black lines as 1
	int threshold = 100;
	int x = 0;
	int error = 0;
	take_picture();
		//int sumThreshold = 0;
		int whiteBool = 0;
		int numWhiteBool = 0;
		for(int i=0; i<320; i++){ 
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
			}else{
				//If the robot can't see any white, it should reverse
				//It reverses fast enough that it hopefully sees white lines again
				set_motor(2, 254);
				set_motor(1, 254);
				sleep1(0, 5000);
				stop(2);
				stop(1);
			}
		}
		if(debug){
			display_picture(0,500000);
		}
		x++;
	return error;
}

void gateOpener(){
	init();
	char address[15] = {'1','3','0','.','1','9','5','.','6','.','1','9','6'};
	connect_to_server(address, 1024);
	char send[24] = {'P','l','e','a','s','e'};
	send_to_server(send);
	char pass[24];
	receive_from_server(pass);
	send_to_server(pass);
	return;
}


// Keeps checking if the robot is at the end of Q3
// It just looks for the number of red pixels that pass the threshold
bool checkEndQ3(bool atEndQ3){
	int threshold = 100;
	//int redBool;
	int numberRedBool = 0;
	take_picture();
	for(int i=0; i<320; i++){
		if(get_pixel(230, i, 0) > threshold){
			numberRedBool++;
		}
	}
	if(numberRedBool > 150){
		atEndQ3 = true;	
	}
	return atEndQ3;
}

int main(){
	init();
	int error = 0;
	//int previousError = 0;
	bool atEndQ3 = false;
	
	//Loops until it hits red thing at the end of Q3
	int previousError = colourCamera();
	gateOpener();
	while(!atEndQ3){
		error = colourCamera();
		motor(error, previousError);
		atEndQ3 = checkEndQ3(atEndQ3);
	}
	//Stopping motors when it sees red
	stop(2);
	stop(1);
}
