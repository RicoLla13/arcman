#ifndef ENTITY_CLASS
#define ENTITY_CLASS

#include <SFML/Graphics.hpp>
#include <string>

class Entity : public sf::Sprite {
    public:
        Entity(int x_pos, int y_pos, sf::Texture& texture);
        virtual ~Entity() {}
};

#endif
