#ifndef SNAKE_H
#define SNAKE_H

#include <Arduino.h>
#include "position.h"

class Snake{
    public:
        void init();
        void move(int dx, int dy);
        void draw();
        void grow();
        uint8_t getLength();
        void setLength(uint8_t newLength);
        Position getPart(uint8_t index);
        bool isDead();
};

#endif