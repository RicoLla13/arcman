#pragma once

#include "static_entity.hpp"

class SmallPellet : public StaticEntity {
    public:
        SmallPellet(const sf::Vector2f& position, const sf::Texture& texture);
};
