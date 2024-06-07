#pragma once

#include "entity.hpp"
#include "ghost.hpp"
#include "../node/node.hpp"


class Player : public Entity {
    private:
        Direction getInput();
        
    public:
        Player(Node* start_node, const sf::Texture& texture, float speed);

        void update(float delta_time) override;
        bool collideGhosts(const std::vector<Ghost*> ghosts);
};
