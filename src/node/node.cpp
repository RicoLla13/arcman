#include "node.hpp"

Node::Node(const sf::Vector2f& position) {
    this->position = position;

    for (int i = 0; i < 4; i++)
        neighbors.push_back(nullptr);
}

void Node::setNodeUp(Node* node) {
    this->neighbors[static_cast<int>(Direction::UP)] = node;
}

void Node::setNodeDown(Node* node) {
    this->neighbors[static_cast<int>(Direction::DOWN)] = node;
}

void Node::setNodeLeft(Node* node) {
    this->neighbors[static_cast<int>(Direction::LEFT)] = node;
}

void Node::setNodeRight(Node* node) {
    this->neighbors[static_cast<int>(Direction::RIGHT)] = node;
}

void Node::setNeighbours(std::vector<Node*> neighbors) {
    this->neighbors = neighbors;
}

Node* Node::getNeighbour(Direction direction) const {
    return neighbors[static_cast<int>(direction)];
}
