#pragma once

#include "static_entity.hpp"

class BigPellet : public StaticEntity {
    public:
        BigPellet(const sf::Vector2f& position, const sf::Texture& texture);
};
