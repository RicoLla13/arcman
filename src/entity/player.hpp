#ifndef PLAYER
#define PLAYER

#include "entity.hpp"
#include "../node/node.hpp"

#include <iostream>

class Player : public Entity {
    private:
        Node* current_node;
        Node* target_node = nullptr;
        Direction direction = Direction::NONE;
        
        bool nodeOvershoot() const;
        bool oppositeDirection(Direction& direction) const;
        Node* getNewTargetNode();
            
    public:
        Player(const sf::Vector2f& grid_position, const sf::Texture& texture, float speed);
        Player(Node* start_node, const sf::Texture& texture, float speed);

        void update(float delta_time) override;
};

#endif
