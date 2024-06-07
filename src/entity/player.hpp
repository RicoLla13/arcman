#pragma once

#include "entity.hpp"
#include "../node/node.hpp"


class Player : public Entity {
    private:
        Direction getInput();
        
    public:
        Player(Node* start_node, const sf::Texture& texture, float speed);

        void update(float delta_time) override;
};
