#pragma once

#include "entity.hpp"
#include "../node/node.hpp"

#include <iostream>

class Ghost : public Entity {
    private:
        int ghost_number;

    public:
        Ghost(Node* start_node, const sf::Texture& texture, float speed, int ghost_number);

        void update(float delta_time) override;
};
