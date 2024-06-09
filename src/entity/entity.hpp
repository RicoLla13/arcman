#pragma once

#include "../global.hpp"

class Entity : public sf::Sprite {
    public:
        Entity();
        Entity(const sf::Texture& texture);
        void setTextureOffset(int x_off, int y_off);
};
