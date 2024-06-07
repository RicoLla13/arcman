#pragma once

#include "../static/static_entity.hpp"
#include "moving_entity.hpp"
#include "ghost.hpp"

class Player : public MovingEntity {
    private:
        Direction getInput();
        
    public:
        Player(Node* start_node, const sf::Texture& texture, float speed);

        void update(float delta_time) override;
        bool collide(StaticEntity* entity);
        bool collideGhosts(const std::vector<Ghost*> ghosts);
};
