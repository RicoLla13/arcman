#include "player.hpp"

Player::Player(Node* start_node, const sf::Texture& texture, float speed) 
    : Entity(start_node, texture, speed) 
{
    this->direction = Direction::RIGHT;
    this->target_node = this->current_node->getNeighbour(this->direction);
    this->start();
}

void Player::updateDirectionQueue() {
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        if(key_presses.empty() || key_presses.back() != Direction::UP)
            key_presses.push(Direction::UP);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        if(key_presses.empty() || key_presses.back() != Direction::DOWN)
            key_presses.push(Direction::DOWN);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        if(key_presses.empty() || key_presses.back() != Direction::LEFT)
            key_presses.push(Direction::LEFT);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        if(key_presses.empty() || key_presses.back() != Direction::RIGHT)
            key_presses.push(Direction::RIGHT);
    }
}

Direction Player::getInput() {
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        return Direction::UP;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        return Direction::DOWN;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        return Direction::LEFT;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        return Direction::RIGHT;

    return this->direction;
}

void Player::update(float delta_time) {
    // this->updateDirectionQueue();
    this->target_node = this->getNewTarget();

    Direction local_direction = this->getInput();

    // std::cout << "current_node: " << (current_node == nullptr) << " target_node: " << (target_node == nullptr) << std::endl;

    if(this->nodeOvershoot()) {
        if(this->current_node != this->target_node) {
            std::cout << "Node overshoot" << std::endl;
            this->stop();
            this->setPosition(this->target_node->getPosition());

            this->current_node = this->target_node;
            this->direction = local_direction;
        }
    }

    if(!this->is_moving) {
        if(this->current_node->getNeighbour(local_direction) != nullptr) {
            this->direction = local_direction;
            this->start();
        }
    }

    if(isOppositeDirection(local_direction, this->direction)) {
        Node* tmp = this->current_node;
        this->current_node = this->target_node;
        this->target_node = tmp;

        this->direction = local_direction;
    }

    this->elapsed_time += delta_time;
    if(this->elapsed_time - this->switch_animation_ms >= 0) {
        this->elapsed_time = 0.0f;
        this->animation_offset = !this->animation_offset;
    }

    this->setTextureOffset(this->animation_offset, static_cast<int>(this->direction));

    this->move(delta_time);
}
