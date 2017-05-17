#include <stdio.h>
#include <time.h>
#include "E101.h"

const kp = 0.5;
const ki = 0;

int motor(int speed){
	set_motor(1,70+speed);
	set_motor(2,70-speed);
	/*while(true){
	set_motor(1,0);
	set_motor(2,0);
	}*/
	return 0;
}

int colourCamera(){ // In the real code, this will be called int colourCamera()
	int threshold = 50;
	while(true){
		take_picture();
		int sumThreshold = 0;
		int whiteBool = 0;
		int error = 0;
		for(int i=1; i<320; i++){
			char white = get_pixel(120,i,3);
			if(white>threshold){
				whiteBool = 1;
				set_pixel(120, i, 0, 255, 0);
				}
			else {
				whiteBool = 0;
				set_pixel(120, i, 255, 0, 0);
				}
			sumThreshold = sumThreshold+white;
			error = error+whiteBool*(i-160);
			double p_signal = error*kp;
			motor(p_signal);
		}
		threshold = sumThreshold/320;
	}
}

int main(){
	init();
	colorCamera();
}
