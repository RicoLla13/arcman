#pragma once

#include "moving_entity.hpp"

class Ghost : public MovingEntity {
    private:
        // An identifier used to define ghost behavior
        GhostName identifier;

        // Compute new valid direction
        Direction getNewDirection();

    public:
        Ghost(Node* start_node, const sf::Texture& texture, float speed, GhostName identifier);

        // Update with delta time
        void update(float delta_time) override;
};
