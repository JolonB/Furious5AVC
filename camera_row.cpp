#include <stdio.h>
#include <time.h>
#include "E101.h"

int main(){
	init();
	int threshold = 50;
	while(true){
		take_picture();
		int sum = 0;
		//int whiteBool = 0;
		for(int i=1; i<320; i++){
			char white = get_pixel(120,i,3);
			if(white>threshold){
				//whiteBool = 1;
				set_pixel(120, i, 0, 255, 0);
				}
			else {
				//whiteBool = 0;
				set_pixel(120, i, 255, 0, 0);
				}
			sum = sum+white/*Bool*(i-160)*/;
		}
		if(sum/320>50){}
		threshold = sum/320; /** I'm not 100% sure about this code, it seems to work decently, but
		y'know, it could be calculated differently to get a more accurate result. Dividing by 400
		* also works pretty well. */
		display_picture(0,500000);
		//printf("%d", sum);
		//printf("\n");
	}
}
