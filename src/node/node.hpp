#ifndef NODE
#define NODE

#include <SFML/Graphics.hpp>

class Node {
    private:
        sf::Vector2f position;
        Node* nodeUp;
        Node* nodeDown;
Node* nodeLeft;
        Node* nodeRight;

    public:
        Node(const sf::Vector2f& position);
        Node(float x, float y) : Node(sf::Vector2f(x, y)) { }

        void setNodeUp(Node* node) { this->nodeUp = node; }
        void setNodeDown(Node* node) { this->nodeDown = node; }
        void setNodeLeft(Node* node) { this->nodeLeft = node; }
        void setNodeRight(Node* node) { this->nodeRight = node; }

        void setPosition(sf::Vector2f position) { this->position = position; }

        Node* getNodeUp() const { return nodeUp; }
        Node* getNodeDown() const { return nodeDown; }
        Node* getNodeLeft() const { return nodeLeft; }
        Node* getNodeRight() const { return nodeRight; }
        std::vector<Node*> getNeighbors() const { return {nodeUp, nodeDown, nodeLeft, nodeRight}; }

        sf::Vector2f getPosition() const { return position; }
};

#endif
