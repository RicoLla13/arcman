#include "player.h"
#include "../exception/custom_exception.h"

Player::Player(int x_pos, int y_pos, float velocity, sf::Texture& texture) : 
    MovingEntity(x_pos, y_pos, velocity, texture), score(0) {}

void Player::move() {
    sf:Sprite::move(x_speed, y_speed);
}

void Player::setDirection(int x_dir, int y_dir) {
    this->x_speed = velocity * x_dir;
    this->y_speed = velocity * y_dir;
}
