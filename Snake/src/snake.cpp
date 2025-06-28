#include "snake.h"
#include "led_matrix.h"

extern LedMatrix ledMatrix;

#define MAX_LENGTH 16

Position snake[MAX_LENGTH];
uint8_t length = 3;

void Snake::init(){
    snake[0] = {4, 4};
    snake[1] = {3, 4};
    snake[2] = {2, 4};
}

void Snake::move(int dx, int dy){
    for(int i = length - 1; i > 0; i--){
        snake[i] = snake[i - 1];
    }
    snake[0].x = (snake[0].x + dx + 8) % 8;
    snake[0].y = (snake[0].y + dy + 8) % 8;
}

void Snake::draw(){
    for(uint8_t i = 0; i < length; i++){
        ledMatrix.draw(snake[i].x, snake[i].y, true);
    }
}

void Snake::grow(){
    if(length < MAX_LENGTH) length++;
}

uint8_t Snake::getLength(){
    return length;
}

void Snake::setLength(uint8_t newLength){
    length = newLength;
}

Position Snake::getPart(uint8_t index){
    return snake[index];
}

bool Snake::isDead(){
    Position head = snake[0];
    for(uint8_t i = 1; i < length; i++) {
        if (snake[i].x == head.x && snake[i].y == head.y) {
            return true;
        }
    }
    return false;
}