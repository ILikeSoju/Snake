#include <Arduino.h>
#include "led_matrix.h"

LedMatrix ledMatrix;

void setup(){
  ledMatrix.init();
  ledMatrix.update();
}

void loop(){

}