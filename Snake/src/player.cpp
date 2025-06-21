#include "player.h"
#include "led_matrix.h"

Player player;
extern LedMatrix ledMatrix;

uint8_t player_x = 2,
        player_y = 2,
        player_lenght = 2;

void Player::moveRight() {
    // Remove last Snake LED
    uint8_t tail = (player_x - player_lenght + 8) % 8;
    ledMatrix.draw(tail, player_y, false);
    // Add new Snake LED
    player_x = (player_x + 1) % 8;
    // Draw new Snake LED
    for (uint8_t i = 0; i < player_lenght; i++) {
        uint8_t segment = (player_x - i + 7) % 8;
        ledMatrix.draw(segment, player_y, true);
    }
} 

void Player::moveLeft() {
    // Remove last Snake LED
    uint8_t tail = (player_x + player_lenght) % 8;
    ledMatrix.draw(tail, player_y, false);
    // Add new Snake LED
    player_x = (player_x + 7) % 8;
    // Draw new Snake LED
    for (uint8_t i = 0; i < player_lenght; i++) {
        uint8_t segment = (player_x - i + 9) % 8;
        ledMatrix.draw(segment, player_y, true);
    }
}

void Player::moveUp() {
    // Remove last Snake LED
    uint8_t tail = (player_y + player_lenght) % 8;
    ledMatrix.draw(player_x, tail, false);
    // Add new Snake LED
    player_y = (player_y + 7) % 8;
    // Draw new Snake LED
    for (uint8_t i = 0; i < player_lenght; i++) {
        uint8_t segment = (player_y - i + 9) % 8;
        ledMatrix.draw(player_x, segment, true);
    }
}

void Player::moveDown() {
    // Remove last Snake LED
    uint8_t tail = (player_y - player_lenght + 8) % 8;
    ledMatrix.draw(player_x, tail, false);
    // Add new Snake LED
    player_y = (player_y + 1) % 8;
    // Draw new Snake LED
    for (uint8_t i = 0; i < player_lenght; i++) {
        uint8_t segment = (player_y - i + 7) % 8;
        ledMatrix.draw(player_x, segment, true);
    }
}