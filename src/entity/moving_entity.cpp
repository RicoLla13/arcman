#include "moving_entity.h"

MovingEntity::MovingEntity(const sf::Vector2f& grid_position, float velocity, const sf::Texture& texture) : 
    Entity(grid_position, texture), velocity(velocity), speed(0, 0) {}

void MovingEntity::move(float delta_time) {
    sf:Sprite::move(speed.x, speed.y);
}

void MovingEntity::setDirection(int x_dir, int y_dir) {
    this->speed.x = velocity * x_dir;
    this->speed.y = velocity * y_dir;
}

