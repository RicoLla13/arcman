#include "player.hpp"

Player::Player(const sf::Vector2f& grid_position, const sf::Texture& texture, float speed) :
    Entity(grid_position, texture, speed) {}

Player::Player(Node* start_node, const sf::Texture& texture, float speed) :
    Entity(start_node->getPosition(), texture, speed), current_node(start_node) {}

void Player::changeNode(Direction& direction, float delta_time) {
    if (direction == Direction::NONE)
        return;
    else if(direction == last_direction) {
        sf::Vector2f target_position = current_node->getPosition();
        sf::Vector2f current_position = getPosition();

        if(std::abs(target_position.x - current_position.x) < speed * delta_time &&
           std::abs(target_position.y - current_position.y) < speed * delta_time) {
            setPosition(target_position);
            setDirection(Direction::NONE);
        } else {
            move(delta_time);
        }

        return;
    }

    while(true) {
        Node* next_node = nullptr;

        switch (direction) {
            case Direction::UP:
                next_node = current_node->getNodeUp();
                break;
            case Direction::DOWN:
                next_node = current_node->getNodeDown();
                break;
            case Direction::LEFT:
                next_node = current_node->getNodeLeft();
                break;
            case Direction::RIGHT:
                next_node = current_node->getNodeRight();
                break;
        }

        if(next_node != nullptr)
            current_node = next_node;
        else
            break;
    }

    last_direction = direction;
    setDirection(direction);
}
