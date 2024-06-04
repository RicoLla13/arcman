#pragma once

#include "entity.hpp"
#include "../node/node.hpp"

#include <iostream>

class Ghost : public Entity {
    public:
        Ghost(const sf::Vector2f& grid_position, const sf::Texture& texture, float speed);
};
