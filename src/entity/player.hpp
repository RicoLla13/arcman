#ifndef PLAYER
#define PLAYER

#include "entity.hpp"
#include "../node/node.hpp"

class Player : public Entity {
    private:
        Node* current_node;
        Direction last_direction;
            
    public:
        Player(const sf::Vector2f& grid_position, const sf::Texture& texture, float speed);
        Player(Node* start_node, const sf::Texture& texture, float speed);

        void changeNode(Direction& direction, float delta_time);
};

#endif
