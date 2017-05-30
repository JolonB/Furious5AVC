#include <stdio.h>
#include <time.h>
#include "E101.h"

float kp =0.4; // seems  like a good value (0.2)
float ki = 0;
float kd = 0;
float sp = 40;
int debug = 0; // set to 1 to debug
int x = 0;
int threshold = 50;

int motor(int err){
	int speed = 50*(err/12880);
	if(x<10){
	set_motor(2,(sp));
	set_motor(1,(sp));
	sleep1(0,400000);
	printf("%d\n",x);
	}
	if(err>=0){
	set_motor(2,-(sp+speed)); //left motor
	set_motor(1,-(sp-2*speed)); //right motor
	printf("%d\n",x);
	}
	if(err<0){
	set_motor(2,-(sp+2*speed));
	set_motor(1,-(sp-speed));
	printf("%d\n",x);
	}
	return 0;
}

int colourCamera(){
	int white;
	while(true){
		x=0;
		take_picture();
		int sumThreshold = 0;
		int whiteBool = 0;
		int error = 0;
		for(int i=1; i<320; i++){
			white = get_pixel(230,i,3);
			if(white>threshold){
					whiteBool = 1;
				//printf("hi");
				//set_pixel(230, i, 0, 255, 0);
				x++;
				}
			else {
				whiteBool = 0;
				//set_pixel(230, i, 255, 0, 0);
				//printf("hi");
				}
		//	sumThreshold = sumThreshold+white;
			error = error+whiteBool*(i-160);
}
		double p_signal = error*kp;
		motor(p_signal);
		//threshold = sumThreshold/320;
		//display_picture(0,500000);
		
	}
return 0;
}

void gateOpener(){
	char address[15] = {'1','3','0','.','1','9','5','.','6','.','1','9','6'};
	connect_to_server(address, 1024);
	char send[24] = {'P','l','e','a','s','e'};
	send_to_server(send);
	char pass[24];
	receive_from_server(pass);
	send_to_server(pass);
	return;
}

int main(){
	init();
	gateOpener();
	colourCamera();
}
