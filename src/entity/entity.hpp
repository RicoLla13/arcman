#pragma once

#include "../global.hpp"

#include <SFML/Graphics.hpp>
#include <string>

class Entity : public sf::Sprite {
    protected:
        float speed_norm;
        float current_speed = 0;
        bool is_moving = false;
        sf::Vector2f velocity;

        void setDirection(Direction direction);
        void move(float delta_time);
        void start();
        void stop();

    public:
        Entity(const sf::Vector2f& grid_position, const sf::Texture& texture, float speed);

        void setTextureOffset(int x_off, int y_off);
        virtual void update(float delta_time) {};
};
