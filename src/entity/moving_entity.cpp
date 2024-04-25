#include "moving_entity.h"

MovingEntity::MovingEntity(const sf::Vector2f& grid_position, float velocity, const sf::Texture& texture, int size) : 
    Entity(grid_position, texture, size), velocity(velocity), speed(0, 0) {}

void MovingEntity::move() {
    sf:Sprite::move(speed);
    grid_position.x = static_cast<int>(getPosition().x / sprite_size);
    grid_position.y = static_cast<int>(getPosition().y / sprite_size);
}

void MovingEntity::setDirection(int x_dir, int y_dir) {
    this->speed.x = velocity * x_dir;
    this->speed.y = velocity * y_dir;
}

