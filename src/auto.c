#include "main.h"

void highFlag(){
  
}

void midFlag(){

}

void skills(){

}

void autonomous() {
  switch(auton){
    case 0:
      skills();
      break;
    case 1:
      break; //None
    case 2:
      highFlag();
      break;
    case 3:
      midFlag();
  }
}
