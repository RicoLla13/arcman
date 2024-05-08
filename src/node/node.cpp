#include "node.hpp"

Node::Node(const sf::Vector2f& position) {
    this->position = position;
    this->nodeUp = nullptr;
    this->nodeDown = nullptr;
    this->nodeLeft = nullptr;
    this->nodeRight = nullptr;
}


