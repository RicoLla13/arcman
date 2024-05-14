#include "node.hpp"

Node::Node(const sf::Vector2f& position) {
    this->position = position;

    for (int i = 0; i < 4; i++)
        neighbors.push_back(nullptr);
}

void Node::setNeighbour(const Direction& direction, Node* node) {
    if(direction == Direction::NONE)
        throw CustomException("[!] #Node :: setNode()# -> Direction cannot be NONE!");
    
    neighbors[static_cast<int>(direction)] = node;
}

void Node::setAllNeighbours(const std::vector<Node*>& neighbors) {
    this->neighbors = neighbors;
}

Node* Node::getNeighbour(const Direction& direction) const {
    return neighbors[static_cast<int>(direction)];
}
