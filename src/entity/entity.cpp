#include "entity.hpp"

Entity::Entity(const sf::Vector2f& grid_position, const sf::Texture& texture, float speed) :
    sf::Sprite(texture), speed(speed) {
        this->setPosition(grid_position);
    }

void Entity::setTextureOffset(int x_off, int y_off) {
    setTextureRect(sf::IntRect(x_off * sprite_size, y_off * sprite_size, sprite_size, sprite_size));
}

void Entity::setDirection(Direction direction) {
    switch(direction) {
        case Direction::UP:
            velocity = sf::Vector2f(0, -speed);
            break;
        case Direction::DOWN:
            velocity = sf::Vector2f(0, speed);
            break;
        case Direction::LEFT:
            velocity = sf::Vector2f(-speed, 0);
            break;
        case Direction::RIGHT:
            velocity = sf::Vector2f(speed, 0);
            break;
        default:
            velocity = sf::Vector2f(0, 0);
            break;
    }
}

void Entity::move(float delta_time) {
    sf::Sprite::move(velocity * delta_time);
}
