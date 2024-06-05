#include "entity.hpp"

Entity::Entity(Node* start_node, const sf::Texture& texture, float speed) 
    : sf::Sprite(texture), speed_norm(speed)
{
    this->setPosition(start_node->getPosition());
}

void Entity::setTextureOffset(int x_off, int y_off) {
    setTextureRect(sf::IntRect(x_off * sprite_size, y_off * sprite_size, sprite_size, sprite_size));
}

void Entity::move(float delta_time) {
    if(is_moving && (direction != Direction::NONE)) {
        current_speed = speed_norm;

        switch(direction) {
            case Direction::UP:
                velocity.x = 0;
                velocity.y = -1;
                break;
            case Direction::DOWN:
                velocity.x = 0;
                velocity.y = -1;
                break;
            case Direction::RIGHT:
                velocity.x = 1;
                velocity.y = 0;
                break;
            case Direction::LEFT:
                velocity.x = -1;
                velocity.y = 0;
                break;
        }
    }
    else
        current_speed = 0;

    sf::Sprite::move(velocity * current_speed * delta_time);
}

void Entity::start() { is_moving = true; }

void Entity::stop() { is_moving = false; }
