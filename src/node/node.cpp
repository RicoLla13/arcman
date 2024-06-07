#include "node.hpp"

Node::Node(const sf::Vector2f& position) {
    this->position = position;

    for (int i = 0; i < 4; i++) {
        neighbors.push_back(nullptr);
        weights.push_back(-1);
    }
}

void Node::setNeighbour(const Direction& direction, Node* node) {
    if(direction == Direction::NONE)
        throw CustomException("[!] #Node :: setNode()# -> Direction cannot be NONE!");
    
    neighbors[static_cast<int>(direction)] = node;

    sf::Vector2f diff = node->getPosition() - this->position;
    int norm = sqrt(diff.x * diff.x + diff.y * diff.y);
    weights[static_cast<int>(direction)] = norm / rect_size + 1;
}

void Node::setAllNeighbours(const std::vector<Node*>& neighbors) {
    this->neighbors = neighbors;
}

Node* Node::getNeighbour(const Direction& direction) const {
    if(direction != Direction::NONE)
        return neighbors[static_cast<int>(direction)];

    return nullptr;
}
