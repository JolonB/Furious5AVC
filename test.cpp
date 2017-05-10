#include <stdio.h>
#include <time.h>
#include "E101.h"


int motor(int err){
	double speed = err*64/12880;
	set_motor(1,64+speed);
	set_motor(2,64-speed);
	/*while(true){
	set_motor(1,0);
	set_motor(2,0);
	}*/
	return 0;
}

int main(){ // In the real code, this will be called int colourCamera()
	init();
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
			motor(error);
			printf("%d\n", error);
		}
		//if(sumThreshold/320>50){}
		threshold = sumThreshold/320; /** I'm not 100% sure about this code, it seems to work decently, but
		y'know, it could be calculated differently to get a more accurate result. Dividing by 400
		* also works pretty well. */
		display_picture(0,500000);
	}
}
