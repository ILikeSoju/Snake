#include "apple.h"
#include "snake.h"
#include "led_matrix.h"

extern Snake snake;
extern LedMatrix ledMatrix;

Position apple;

void Apple::spawn(){
    bool position_valid = false;
    while (!position_valid) {
        apple.x = random(0, 8);
        apple.y = random(0, 8);

        position_valid = true;
        for(uint8_t i = 0; i < snake.getLength(); i++){
            Position part = snake.getPart(i);
            
            if(part.x == apple.x && part.y == apple.y){
                position_valid = false;
                break;
            }
        }
    }
}

void Apple::draw(){
    ledMatrix.draw(apple.x, apple.y, true);
}

Position Apple::getPosition(){
    return apple;
}