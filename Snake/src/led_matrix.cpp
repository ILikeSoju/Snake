#include "led_matrix.h"

LedMatrix ledMatrix;

uint8_t coordinates[8][8] = {
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0}
};

void LedMatrix::init(){
    pinMode(LED_MATRIX_CS, OUTPUT);
    digitalWrite(LED_MATRIX_CS, HIGH);

    SPI.setMOSI(LED_MATRIX_MOSI);
    SPI.setMISO(LED_MATRIX_MISO);
    SPI.setSCLK(LED_MATRIX_CLK);
    SPI.begin();
    SPI.beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE0));

    sendData(0x09, 0x00);
    sendData(0x0A, 0x06);
    sendData(0x0B, 0x07);
    sendData(0x0C, 0x01);
    sendData(0x0f, 0X00);
}

void LedMatrix::sendData(uint8_t adress, uint8_t data){
    digitalWrite(LED_MATRIX_CS, LOW);
    SPI.transfer(adress);
    SPI.transfer(data);
    digitalWrite(LED_MATRIX_CS, HIGH);
}

void LedMatrix::update(){
    for(uint8_t row = 0; row < 8; row++){
        uint8_t value = 0;
        for(uint8_t colum = 0; colum < 8; colum++){
            if(coordinates[row][colum]) value |= (1 << (7 - colum));
        }
        sendData(row + 1, value);
    }
}

void LedMatrix::draw(uint8_t x, uint8_t y, bool add){
    if(add) coordinates[y][x] = 1;
    else coordinates[y][x] = 0;
}

void LedMatrix::clear(){
    for(uint8_t y = 0; y < 8; y++){
        for(uint8_t x = 0; x < 8; x++){
            coordinates[y][x] = 0;
        }
    }
}