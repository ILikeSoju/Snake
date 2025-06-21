#include "led_matrix.h"

void LedMatrix::init(){
    pinMode(LED_MATRIX_CS, OUTPUT);
    digitalWrite(LED_MATRIX_CS, HIGH);

    SPI.setMOSI(LED_MATRIX_MOSI);
    SPI.setMISO(LED_MATRIX_MISO);
    SPI.setSCLK(LED_MATRIX_CLK);
    SPI.begin();
    SPI.beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE0));
}

void LedMatrix::sendData(unsigned char adress, unsigned char data){
    digitalWrite(LED_MATRIX_CS, LOW);
    SPI.transfer(adress);
    SPI.transfer(data);
    digitalWrite(LED_MATRIX_CS, HIGH);
}

void LedMatrix::update(){
    sendData(0x09, 0x00);
    sendData(0x0A, 0x06);
    sendData(0x0B, 0x07);
    sendData(0x0C, 0x01);
    sendData(0x0f, 0X00);

    for(int i = 1; i < 9; i++){
        sendData(i, 0xf0);
    }
}