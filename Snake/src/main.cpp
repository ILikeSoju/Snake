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
#define RESTART PB4

#define BTRX PB11
#define BTTX PB10
#define ENABLE PB12
#define STATE PA1

#define SNAKE_START_LENGTH 2

LiquidCrystal_PCF8574 lcd(0x27);
static HardwareTimer timer = HardwareTimer(TIM6);
HardwareSerial SerialBT(BTRX,BTTX);

enum direction {RIGHT, LEFT, UP, DOWN};
direction current_direction;

uint8_t gameSpeed = 200;

volatile int apples = 0;
int highscore = 0;

volatile bool LCDGameOver = false;

void isr_restart(){
  if(LCDGameOver) LCDGameOver = false;
  apples = 0;
  current_direction = RIGHT;
  snake.setLength(SNAKE_START_LENGTH);
  if(snake.isDead()) !snake.isDead();
  ledMatrix.clear();
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.printf("Snake by VAA");
  delay(1000);
}

void isr_main(){
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
  Position object_apple = apple.getPosition();

  if(head.x == object_apple.x && head.y == object_apple.y){
    snake.grow();
    apples++;
    apple.spawn();
  }

  if (snake.isDead()) {
    if(highscore < apples) highscore = apples;
    lcd.clear();
    if(!LCDGameOver){
      LCDGameOver = true;
      lcd.setCursor(0,0);
      lcd.printf("GAME OVER");
      lcd.setCursor(0,1);
      lcd.printf("GAME OVER");
      delay(1000);
    }
    lcd.setCursor(0,0);
    lcd.printf("Score: %d Best: %d, apples", apples, highscore);
    lcd.setCursor(0, 1);
    lcd.printf("PB4 -> Restart");
  } else {
    lcd.setCursor(0,1);
    lcd.printf("Score: %d", apples);
  }

  ledMatrix.clear();
  snake.draw();
  apple.draw();
  ledMatrix.update();
  lcd.setCursor(0, 1);
}

void setup(){
  analogReadResolution(6);

  timer.setPrescaleFactor(32000);
  timer.setOverflow(300);
  timer.attachInterrupt(isr_main);
  timer.resume();

  Serial.begin(9600);
  SerialBT.begin(9600);
  delay(100);
  pinMode(STATE,INPUT);
  Serial.println("Bluetooth erfolgreich verbunden");
  

  pinMode(RESTART, INPUT_PULLDOWN);
  attachInterrupt(RESTART, isr_restart, RISING);
  lcd.begin(16,2);
  lcd.clear();
  lcd.setBacklight(255);
  lcd.setCursor(0,0);
  lcd.printf("Snake by VAA");

  randomSeed(0);

  snake.setLength(SNAKE_START_LENGTH);
  current_direction = RIGHT;

  ledMatrix.init();
  snake.init();
  apple.spawn();
}

void loop(){
  if (SerialBT.available()) {
  String command = SerialBT.readStringUntil('\n');
  command.trim();         // entfernt \n, \r und Leerzeichen
  command.toUpperCase();  // "up" → "UP"
  Serial.println(command);

  if (command == "UP"    && (current_direction == RIGHT || current_direction == LEFT)) current_direction = UP;
  if (command == "DOWN"  && (current_direction == RIGHT || current_direction == LEFT)) current_direction = DOWN;
  if (command == "LEFT"  && (current_direction == UP || current_direction == DOWN))    current_direction = LEFT;
  if (command == "RIGHT" && (current_direction == UP || current_direction == DOWN))    current_direction = RIGHT;
  if (command == "RESTART") isr_restart();
}
}