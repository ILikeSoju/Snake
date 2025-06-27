#ifndef APPLE_H
#define APPLE_H

#include <Arduino.h>
#include "position.h"

class Apple{
    public:
        void spawn();
        void draw();
        Position getPosition();
};

#endif