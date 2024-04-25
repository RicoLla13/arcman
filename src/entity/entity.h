#ifndef ENTITY_CLASS
#define ENTITY_CLASS

#include <SFML/Graphics.hpp>
#include <string>

class Entity : public sf::Sprite {
    public:
        sf::Vector2f grid_position;

        Entity(const sf::Vector2f& position, const sf::Vector2f& grid_position, sf::Texture& texture);
        void setTextureOffset(int x_off, int y_off, int size);
        virtual ~Entity() {}
};

#endif
