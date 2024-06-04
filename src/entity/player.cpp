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
        if(key_presses.empty() || key_presses.back() != Direction::UP)
            key_presses.push(Direction::UP);
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        if(key_presses.empty() || key_presses.back() != Direction::DOWN)
            key_presses.push(Direction::DOWN);
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        if(key_presses.empty() || key_presses.back() != Direction::LEFT)
            key_presses.push(Direction::LEFT);
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        if(key_presses.empty() || key_presses.back() != Direction::RIGHT)
            key_presses.push(Direction::RIGHT);
    }
}

Direction Player::computeDirection() {
    if(!key_presses.empty()) {
        Direction d = this->key_presses.front();
        this->key_presses.pop();
        return d;
    }

    return this->direction;
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
    target_node = getNewTargetNode();

    if(nodeOvershoot()) {
        if(current_node != target_node) {
            setPosition(target_node->getPosition());
            current_node = target_node;

            direction = computeDirection();

            stop();
        }
    }
    else
        start();
    
    this->getValidKeyPress();

    if(isOppositeDirection(this->key_presses.front(), direction)) {
        Node* tmp = current_node;
        current_node = target_node;
        target_node = tmp;

        direction = computeDirection();
    }

    if(!this->is_moving) {
        direction = computeDirection();
    }

    elapsed_time += delta_time;
    if(elapsed_time - mouth_animation_time >= 0) {
        elapsed_time = 0.0f;
        mouth_offset = !mouth_offset;
    }

    setTextureOffset(mouth_offset, static_cast<int>(direction));

    setDirection(direction);
    move(delta_time);
}
