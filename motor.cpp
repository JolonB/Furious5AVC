#include <stdio.h>
#include <time.h>
#include "E101.h"

int main(){
  init();
  set_motor(1,102);
  sleep1(5,0);
  set_motor(2,102); 
  sleep1(5,0); 
  set_motor(1,0);
  sleep1(5,0);
  set_motor(2,0);
}