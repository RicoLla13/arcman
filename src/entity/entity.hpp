#pragma once

#include "../global.hpp"

/*
 * Extension of sf::Sprite
 * Just for the setTextureOffset method
 * and to have a base for the next classes
 */
class Entity : public sf::Sprite {
    public:
        Entity(const sf::Texture& texture);
        void setTextureOffset(int x_off, int y_off);
};
