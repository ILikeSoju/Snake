#include "led_matrix.h"

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

void LedMatrix::update(uint8_t coordinates[8][8]){
    for(uint8_t row = 0; row < 8; row++){
        uint8_t value = 0;
        for(uint8_t colum = 0; colum < 8; colum++){
            if(coordinates[colum][row]) value |= (1 << (7 - colum));
        }
        sendData(row + 1, value);
    }
}