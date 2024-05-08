#ifndef ENTITY_CLASS
#define ENTITY_CLASS

#include "../global.hpp"

#include <SFML/Graphics.hpp>
#include <string>

class Entity : public sf::Sprite {
    protected:
        float speed;
        sf::Vector2f velocity;

    public:
        Entity(const sf::Vector2f& grid_position, const sf::Texture& texture, float speed);

        void setTextureOffset(int x_off, int y_off);
        void setDirection(Direction direction);
        void move(float delta_time);
        virtual void update(float delta_time) {};
};

#endif
