#include <Arduino.h>
#include "LiquidCrystal_PCF8574.h"
#include "led_matrix.h"
#include "snake.h"
#include "apple.h"

extern LedMatrix ledMatrix;
extern Snake snake;
extern Apple apple;

#define JOYSTICK_X PC0
#define JOYSTICK_Y PC1

LiquidCrystal_PCF8574 lcd(0x27);

enum direction {RIGHT, LEFT, UP, DOWN};
direction current_direction;

uint8_t gameSpeed = 200;

int apples = 0;

void setup(){
  analogReadResolution(6);
  lcd.begin(16,2);
  lcd.clear();
  lcd.setBacklight(255);
  lcd.setCursor(0,0);
  lcd.printf("SNAKE: WONYOUNG");

  randomSeed(0);

  current_direction = RIGHT;

  ledMatrix.init();
  snake.init();
  apple.spawn();
}

void loop(){
  switch (current_direction)
  {
  case RIGHT:
    if(analogRead(JOYSTICK_Y) > 43) current_direction = UP;
    if(analogRead(JOYSTICK_Y) < 43) current_direction = DOWN;
    break;
  case LEFT:
    if(analogRead(JOYSTICK_Y) > 43) current_direction = UP;
    if(analogRead(JOYSTICK_Y) < 43) current_direction = DOWN;
    break;
  case UP:
    if(analogRead(JOYSTICK_X) > 36) current_direction = RIGHT;
    if(analogRead(JOYSTICK_X) < 36) current_direction = LEFT;
    break;
  case DOWN:
    if(analogRead(JOYSTICK_X) > 36) current_direction = RIGHT;
    if(analogRead(JOYSTICK_X) < 36) current_direction = LEFT;
    break;
  }

  if(!snake.isDead()){
    if(current_direction == RIGHT) snake.move(1, 0);
    if(current_direction == LEFT) snake.move(-1, 0);

    if(current_direction == UP) snake.move(0, 1);
    if(current_direction == DOWN) snake.move(0, -1);
  }

  Position head = snake.getPart(0);
  Position object = apple.getPosition();

  if(head.x == object.x && head.y == object.y){
    snake.grow();
    apples++;
    apple.spawn();
  }

  if (snake.isDead()) {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("GAME OVER");
  }

  ledMatrix.clear();
  snake.draw();
  apple.draw();
  ledMatrix.update();
  lcd.setCursor(0, 1);
  lcd.printf("Score: %d", apples);
  delay(gameSpeed);
}