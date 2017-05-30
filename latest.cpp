// I can't confirm this code works until it has been tested. Hopefully it will be tidier than before.

#include <stdio.h>
#include <time.h>
#include "E101.h"

float kp = 0.3; // Figure out a good value. 0.3 is nice.
float kd = 0; // I guess this isn;t getting implemented?
int sp = 50; // May need to be adjusted if conditions change slightly.
int threshold = 50; // Could be changed to 100 if we feel it's necessary.
int numWhite = 0; //counts the number of white pixels in one row of an image.
bool atEndQ3 = false; //used to tell the program if it has finished quadrant 3.
int numRed = -1; //counts the number of red pixels.
int numBlue = -1;
int numGreen = -1;
int turn90 = 40; //speed when turning 90 degrees.
int turnSleepS = 0; //time (in seconds) it turns for.
int turnSleepMs = 700000; //time (in ms) it turns for.
bool q3 = false;
bool leftTurn = false;
bool rightTurn = false;
int prevError = 0;

// Run the motor using the error signal value.
void motor(int err){
	int speed = 100*err/12880;
	if(numWhite<10 && (numWhite>0 || !q3)){
		set_motor(1,-30);
		set_motor(2,-10);
		set_motor(1,-20);
		set_motor(2,0);
		set_motor(1, sp+20); //right
		set_motor(2, sp); //left
	}
	else if(numWhite==0 && q3){
		if(leftTurn){
			set_motor(1,-turn90);
			set_motor(2,turn90);
		}
		else if(rightTurn){
			set_motor(1,turn90);
			set_motor(2,turn90);
		}
		sleep1(turnSleepS, turnSleepMs);
		set_motor(1,0);
		set_motor(2,0);
		sleep1(1,0);
	}
	else if(err>=0){
		set_motor(2,-(sp+speed)); //left motor
		set_motor(1,-(sp-2*speed)); //right motor
	}
	else if(err<0){
		set_motor(2,-(sp+2*speed)); //left
		set_motor(1,-(sp-speed)); //right
	}
}

// Open the gate.
void gateOpener(){
	char address[15] = {'1','3','0','.','1','9','5','.','6','.','1','9','6'};
	connect_to_server(address, 1024);
	char send[24] = {'P','l','e','a','s','e'};
	send_to_server(send);
	char pass[24];
	receive_from_server(pass);
	send_to_server(pass);
}

// Check colour values of pixels and calculate error.
int colourCamera(){
	rightTurn = false;
	leftTurn = false;
	take_picture();
	numWhite = 0;
	int whiteBool = 0;
	int error = 0;
	numRed = 0;
	numBlue = 0;
	numGreen = 0;
	for(int i=1; i<320; i++){
		char white = get_pixel(230,i,3);
		char red = get_pixel(230,i,0);
		char blue = get_pixel(230,i,1);
		char green = get_pixel(230,i,2);
		if(white>threshold){
			whiteBool = 1;
			numWhite++;
		}
		else {
			whiteBool = 0;
		}
		if(red>threshold){
			numRed++;
		}
		if(blue>threshold){
			numBlue++;
		}
		if(green>threshold){
			numGreen++;
		}
		error = error+whiteBool*(i-160);
	}
	if(numWhite==0){
		if(prevError>0){
			rightTurn = true;
		}
		else if(prevError<=0){
			leftTurn = true;
		}
	}
	prevError = error;
	double p_signal = error*kp;
	return p_signal;
}

void quadFour(){
	while(true){
		set_motor(2,-sp);
		set_motor(1,-sp);
		int adc_reading = read_analog(0);
		if (adc_reading>350){
			return;
		}
	}
}

// The first function to run when the code starts.
int main(){
	init();
	gateOpener(); // open the gate.
	while(numRed<200 || numGreen>100 || numBlue>100){
		double error = colourCamera(); // retrieve error value
		motor(error); // control the motors.
		if(numWhite>310){
			printf("%d ",numWhite);
			q3=true;
		}
	}
	quadFour();
	set_motor(1,0);
	set_motor(2,0);
}
