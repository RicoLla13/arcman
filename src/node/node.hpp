#ifndef NODE
#define NODE

#include "../global.hpp"
#include "../exception/custom_exception.hpp"

#include <SFML/Graphics.hpp>
#include <math.h>

class Node {
    private:
        sf::Vector2f position;
        std::vector<Node*> neighbors;
        std::vector<int> weights;

    public:
        Node(const sf::Vector2f& position);
        Node(float x, float y) : Node(sf::Vector2f(x, y)) { }

        void setNeighbour(const Direction& direction, Node* node); 
        void setAllNeighbours(const std::vector<Node*>& neighbors);

        void setPosition(const sf::Vector2f& position) { this->position = position; }

        Node* getNeighbour(const Direction& direction) const;
        int getWeight(const Direction& direction) const { return weights[static_cast<int>(direction)]; }
        std::vector<Node*> getAllNeighbours() const { return neighbors; }

        sf::Vector2f getPosition() const { return position; }
};

#endif
