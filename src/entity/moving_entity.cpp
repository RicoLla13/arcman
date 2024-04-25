#include "moving_entity.h"

MovingEntity::MovingEntity(const sf::Vector2f& position, const sf::Vector2f& grid_position, float velocity, sf::Texture& texture) : 
    Entity(position, grid_position, texture), velocity(velocity), speed(0, 0) {}

void MovingEntity::move() {
    sf:Sprite::move(speed);
}

void MovingEntity::setDirection(int x_dir, int y_dir) {
    this->speed.x = velocity * x_dir;
    this->speed.y = velocity * y_dir;
}

