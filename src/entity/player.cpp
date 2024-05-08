#include "player.hpp"

Player::Player(const sf::Vector2f& grid_position, const sf::Texture& texture, float speed) :
    Entity(grid_position, texture, speed) {}

Player::Player(Node* start_node, const sf::Texture& texture, float speed) :
    Entity(start_node->getPosition(), texture, speed), current_node(start_node) {}

Node* Player::getNewTargetNode() {
    if(direction != Direction::NONE)
        if(current_node->getNeighbour(direction) != nullptr)
            return current_node->getNeighbour(direction);

    return current_node;
}

bool Player::nodeOvershoot() const {
     if(target_node == nullptr)
        return false;

    sf::Vector2f target_position = target_node->getPosition() - current_node->getPosition();
    sf::Vector2f player_position = getPosition() - current_node->getPosition();

    float tp_length = target_position.x * target_position.x + target_position.y * target_position.y;
    float pp_length = player_position.x * player_position.x + player_position.y * player_position.y;

    return pp_length >= tp_length;
}

bool Player::oppositeDirection(Direction& direction) const {
    if(direction == Direction::UP && this->direction == Direction::DOWN)
        return true;
    else if(direction == Direction::DOWN && this->direction == Direction::UP)
        return true;
    else if(direction == Direction::LEFT && this->direction == Direction::RIGHT)
        return true;
    else if(direction == Direction::RIGHT && this->direction == Direction::LEFT)
        return true;
    return false;
}

void Player::update(float delta_time) {
    setDirection(direction);
    move(delta_time);

    Direction temp_direction = direction;

    // manage key presses
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        direction = Direction::UP;
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        direction = Direction::DOWN;
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        direction = Direction::LEFT;
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        direction = Direction::RIGHT;

    target_node = getNewTargetNode();

    if(nodeOvershoot()) {
        current_node = target_node;
        target_node = getNewTargetNode();
        
        if(target_node == current_node)
            direction = Direction::NONE;

        setPosition(current_node->getPosition());
    }
}
