#include <Arduino.h>
#include "led_matrix.h"
#include "player.h"

extern LedMatrix ledMatrix;
extern Player player;

uint8_t gameSpeed = 200;

void setup(){
  ledMatrix.init();
  ledMatrix.update();
}

void loop(){
  player.moveRight();
  ledMatrix.update();
  delay(gameSpeed);
}