#pragma once

#include "entity.hpp"
#include "../node/node.hpp"
#include "../global.hpp"

#include <iostream>

class Ghost : public Entity {
    private:
        GhostName identifier;

    public:
        Ghost(Node* start_node, const sf::Texture& texture, float speed, GhostName identifier);

        void update(float delta_time) override;
};
