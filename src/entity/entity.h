#ifndef ENTITY_CLASS
#define ENTITY_CLASS

#include "../global.h"

#include <SFML/Graphics.hpp>
#include <string>

class Entity : public sf::Sprite {
    public:
        Entity(const sf::Vector2f& grid_position, const sf::Texture& texture);
        void setTextureOffset(int x_off, int y_off);
        virtual ~Entity() {}
};

#endif
