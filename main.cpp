// I can't confirm this code works until it has been tested. Hopefully it will be tidier than before.

#include <stdio.h>
#include <time.h>
#include "E101.h"

float kp =0.3; // Figure out a good value. 0.3 is nice.
float kd = 0; // I guess this isn;t getting implemented?
int sp = 50; // May need to be adjusted if conditions change slightly.
int threshold = 50; // Could be changed to 100 if we feel it's necessary.

int motor(int err, int x){
	int speed = 100*err/12880;
	if(x<10){
	set_motor(1, sp);
	set_motor(2, sp);
//	sleep1(0,500);
	}
	else if(err>=0){
	set_motor(2,-(sp+speed)); //left motor
	set_motor(1,-(sp-2*speed)); //right motor
	}
	else if(err<0){
	set_motor(2,-(sp+2*speed));
	set_motor(1,-(sp-speed));
	}
	return 0;
}

int gateOpener(){
	char address[15] = {'1','3','0','.','1','9','5','.','6','.','1','9','6'};
	connect_to_server(address, 1024);
	char send[24] = {'P','l','e','a','s','e'};
	send_to_server(send);
	char pass[24];
	receive_from_server(pass);
	send_to_server(pass);
	return 1;
}


int colourCamera(){
	take_picture();
	int numWhite = 0;
	int whiteBool = 0;
	int error = 0;
	for(int i=1; i<320; i++){
		char white = get_pixel(230,i,3);
		if(white>threshold){
			whiteBool = 1;
			numWhite++;
		}
		else {
			whiteBool = 0;
		}
		error = error+whiteBool*(i-160);
		double p_signal = error*kp;
			
		//motor(p_signal, numWhite);
	}
	return p_signal;
}

int main(){
	init();
	while(true){
		int gateDone = gateOpener();
		if(gateDone = 1){
			break;
		}
	}
	while(true){
		double error = colourCamera();
		motor(error);
	}
}
