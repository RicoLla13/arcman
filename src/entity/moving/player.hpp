#pragma once

#include "../static/static_entity.hpp"
#include "moving_entity.hpp"
#include "ghost.hpp"

class Player : public MovingEntity {
    private:
        // Get a new valid keyboard input
        Direction getInput();
        
    public:
        Player(Node* start_node, const sf::Texture& texture, float speed);

        // Update with delta time
        void update(float delta_time) override;
        // Collide with static entity
        bool collide(StaticEntity* entity);
        // Collide with a vector of ghosts
        bool collideGhosts(const std::vector<Ghost*> ghosts);
};
