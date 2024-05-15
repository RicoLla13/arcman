#include "entity.hpp"

Entity::Entity(const sf::Vector2f& grid_position, const sf::Texture& texture, float speed) :
    sf::Sprite(texture), speed_norm(speed) {
        this->setPosition(grid_position);
    }

void Entity::setTextureOffset(int x_off, int y_off) {
    setTextureRect(sf::IntRect(x_off * sprite_size, y_off * sprite_size, sprite_size, sprite_size));
}

void Entity::setDirection(Direction direction) {
    switch(direction) {
        case Direction::UP:
            velocity = sf::Vector2f(0, -1);
            break;
        case Direction::DOWN:
            velocity = sf::Vector2f(0, 1);
            break;
        case Direction::LEFT:
            velocity = sf::Vector2f(-1, 0);
            break;
        case Direction::RIGHT:
            velocity = sf::Vector2f(1, 0);
            break;
        default:
            velocity = sf::Vector2f(0, 0);
            break;
    }
}

void Entity::move(float delta_time) {
    sf::Sprite::move(velocity * current_speed * delta_time);
}

void Entity::start() {
    current_speed = speed_norm;
    is_moving = true;
}

void Entity::stop() {
    current_speed = 0;
    is_moving = false;
}
