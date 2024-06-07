#pragma once

#include "moving_entity.hpp"

class Ghost : public MovingEntity {
    private:
        GhostName identifier;

        Direction getNewDirection();

    public:
        Ghost(Node* start_node, const sf::Texture& texture, float speed, GhostName identifier);

        void update(float delta_time) override;
};
