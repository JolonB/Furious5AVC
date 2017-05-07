#include <stdio.h>
#include <time.h>
#include "E101.h"

int main(){
	init();
	sleep1(3,0);
	printf("start\n");
	int i = 0;
	int sum = 0;
	while(i<50){
	take_picture();
	char white = get_pixel(160,120,3);
	printf("%d\n", white);
	sleep1(0,50000);
	sum = sum+white;
	i++;
}
double average = (sum/i);
printf("%f",average);
}
