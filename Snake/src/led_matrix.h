#ifndef LED_MATRIX_H
#define LED_MATRIX_H

#include <Arduino.h>
#include <SPI.h>

#define LED_MATRIX_CS PB12
#define LED_MATRIX_MOSI PB15
#define LED_MATRIX_MISO PB14
#define LED_MATRIX_CLK PB13

class LedMatrix{
    public:
        void init();
        void update();
        void sendData(unsigned char adress, unsigned char data);
};

#endif