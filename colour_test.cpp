#include <stdio.h>
#include <time.h>
#include "E101.h"

int main(){
	init();
	while(true){
	take_picture();
	char white = get_pixel(160,120,3);
	char red = get_pixel(160,120,0);
	if(white>15){
		printf("white\n");
		}
	else if(red>8){
		printf("red\n");
		}
	else{
		printf("black\n");
		}
		sleep1(0,50000);
	}
}
