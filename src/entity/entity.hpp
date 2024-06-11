#pragma once

#include "../global.hpp"

class Entity : public sf::Sprite {
    public:
        Entity(const sf::Texture& texture);
        void setTextureOffset(int x_off, int y_off);
};
