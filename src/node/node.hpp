#ifndef NODE
#define NODE

#include "../global.hpp"

#include <SFML/Graphics.hpp>

class Node {
    private:
        sf::Vector2f position;
        std::vector<Node*> neighbors;

    public:
        Node(const sf::Vector2f& position);
        Node(float x, float y) : Node(sf::Vector2f(x, y)) { }

        void setNodeUp(Node* node); 
        void setNodeDown(Node* node); 
        void setNodeLeft(Node* node);
        void setNodeRight(Node* node);
        void setNeighbours(std::vector<Node*> neighbors);

        void setPosition(sf::Vector2f position) { this->position = position; }

        Node* getNeighbour(Direction direction) const;
        std::vector<Node*> getAllNeighbours() const { return neighbors; }

        sf::Vector2f getPosition() const { return position; }
};

#endif
