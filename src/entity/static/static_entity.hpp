#pragma once

#include "../entity.hpp"

class StaticEntity : public Entity {
    public:
        bool is_eaten = false;
        StaticEntity(const sf::Vector2f& position, const sf::Texture& texture);
};
