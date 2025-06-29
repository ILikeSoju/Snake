#ifndef LED_MATRIX_H
#define LED_MATRIX_H

#include <Arduino.h>
#include <SPI.h>

#define LED_MATRIX_CS PB6
#define LED_MATRIX_MOSI PB15
#define LED_MATRIX_MISO PB14
#define LED_MATRIX_CLK PB13

class LedMatrix{
    private:
        void sendData(uint8_t adress, uint8_t data);
    public:
        void init();
        void update();
        void draw(uint8_t x, uint8_t y, bool add);
        void clear();
};

#endif