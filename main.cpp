#include <stdio.h>
#include <time.h>
#include "E101.h"

float kp =0.5; // figure out a good value. 0.5 kind of worked
float ki = 0;
float kd = 0;
float sp = 50;
bool debug = false; // set to true to debug

int motor(int err){
	int speed = 100*err/12880;
	if(err>=0){
	set_motor(2,-(sp+speed)); //left motor
	set_motor(1,-(sp-2*speed)); //right motor
	}
	if(err<0){
	set_motor(2,-(sp+2*speed));
	set_motor(1,-(sp-speed));
	}
	return 0;
}

void gate(){
	char address[15] = {'1','3','0','.','1','9','5','.','6','.','1','9','6'};
	connect_to_server(address, 1024);
	char send[24] = {'P','l','e','a','s','e'};
	send_to_server(send);
	char pass[24];
	receive_from_server(pass);
	send_to_server(pass);
	return;
}

int colourCamera(){
	int threshold = 50;
	int x = 0;
	while(true){
		take_picture();
		int sumThreshold = 0;
		int whiteBool = 0;
		int error = 0;
		for(int i=1; i<320; i++){ // perhaps we could change the number of pixels it detects in the first quadrant to prevent it detecting the wrong line
			char white = get_pixel(230,i,3);
			if(white>threshold){
				whiteBool = 1;
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
			motor(p_signal);
		}
		//threshold = sumThreshold/320;
		if(debug){
			display_picture(0,500000);
		}
		x++;
	}
return 0;
}

int main(){
	init();
	colourCamera();
}
