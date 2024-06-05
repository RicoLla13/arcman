#pragma once

#include "entity.hpp"
#include "../node/node.hpp"

#include <iostream>
#include <queue>

class Player : public Entity {
    private:
        std::queue<Direction> key_presses;
        
    public:
        Player(Node* start_node, const sf::Texture& texture, float speed);

        void update(float delta_time) override;
};
