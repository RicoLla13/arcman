#include "entity.hpp"

Entity::Entity(Node* start_node, const sf::Texture& texture, float speed) 
    : sf::Sprite(texture), speed_norm(speed), current_node(start_node)
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
                velocity.y = 1;
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

bool Entity::nodeOvershoot() const {
    if(target_node == nullptr)
            return false;

    sf::Vector2f target_position = target_node->getPosition() - current_node->getPosition();
    sf::Vector2f player_position = getPosition() - current_node->getPosition();

    float tp_length = target_position.x * target_position.x + target_position.y * target_position.y;
    float pp_length = player_position.x * player_position.x + player_position.y * player_position.y;

    return pp_length >= tp_length;
}

Node* Entity::getNewTarget() const {
    if(this->direction != Direction::NONE)
        if(this->current_node->getNeighbour(this->direction) != nullptr)
            return this->current_node->getNeighbour(this->direction);

    return this->current_node;
}
