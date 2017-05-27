#include <stdio.h>
#include <time.h>
#include "E101.h"

float turn90 = 50; // adjust this value to change how fast it turns for
float turnSleepS = 0;
float turnSleepMs = 700000;

void turnAC(){ // Turn 90 degrees anti-clockwise
	set_motor(1,-turn90);
	set_motor(2,turn90);
	sleep1(turnSleepS,turnSleepMs);
	set_motor(1,0);
	set_motor(2,0);
	return;
}

void turnC(){ // Turn 90 degrees clockwise
	set_motor(1,turn90);
	set_motor(2,-turn90);
	sleep1(turnSleepS,turnSleepMs);
	set_motor(1,0);
	set_motor(2,0);
	return;	
}

int main(){
	init();
	turnAC();
	sleep1(2,0);
	turnC();
}
