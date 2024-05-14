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

void Player::getValidKeyPress() {
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        direction = Direction::UP;
        std::cout << "W pressed" << std::endl;
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        direction = Direction::DOWN;
        std::cout << "S pressed" << std::endl;
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        direction = Direction::LEFT;
        std::cout << "S pressed" << std::endl;
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        direction = Direction::RIGHT;
        std::cout << "S pressed" << std::endl;
    }
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

void Player::update(float delta_time) {
    // setDirection(direction);
    // move(delta_time);

    // manage key presses
    getValidKeyPress();

    target_node = getNewTargetNode();

    if(current_node != target_node) {
        setPosition(target_node->getPosition());
        current_node = target_node;

        direction = Direction::NONE;
    }

    std::cout << static_cast<int>(direction) << std::endl;
}
