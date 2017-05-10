#include <stdio.h>
#include <time.h>
#include "E101.h"

int main(){
  init();
  set_motor(1,102);
  set_motor(2,102); 
  sleep1(2,0); 
  set_motor(1,0);
  set_motor(2,0);
}

//* This code makes both motors move forwards for 2 seconds 
