#ifndef ENTITY_CLASS
#define ENTITY_CLASS

#include <SFML/Graphics.hpp>
#include <string>

class Entity : public sf::Sprite {
    protected:
        int sprite_size;
        sf::Vector2f grid_position;

    public:
        Entity(const sf::Vector2f& grid_position, const sf::Texture& texture, int size);
        void setTextureOffset(int x_off, int y_off, int size);
        sf::Vector2f getGridPosition() const;
        virtual ~Entity() {}
};

#endif
