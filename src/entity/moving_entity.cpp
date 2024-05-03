#include "moving_entity.h"

MovingEntity::MovingEntity(const sf::Vector2f& grid_position, float velocity, const sf::Texture& texture) : 
    Entity(grid_position, texture), velocity(velocity), direction(0, 0) {}

void MovingEntity::move(float delta_time) {
    sf::Sprite::move(direction * velocity * delta_time);
}

void MovingEntity::setDirection(Direction direction) {
    switch(direction) {
        case Direction::UP:
            this->direction.x = 0;
            this->direction.y = -1;
            break;
        case Direction::DOWN:
            this->direction.x = 0;
            this->direction.y = 1;
            break;
        case Direction::LEFT:
            this->direction.x = -1;
            this->direction.y = 0;
            break;
        case Direction::RIGHT:
            this->direction.x = 1;
            this->direction.y = 0;
            break;
        case Direction::NONE:
            this->direction.x = 0;
            this->direction.y = 0;
            break;
    }
}
