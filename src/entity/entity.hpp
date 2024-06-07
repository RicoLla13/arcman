#pragma once

#include "../global.hpp"
#include "../node/node.hpp"

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

class Entity : public sf::Sprite {
    protected:
        float speed_norm;
        float current_speed = 0;
        bool is_moving = false;
        Direction direction = Direction::NONE;
        sf::Vector2f velocity;

        Node* current_node;
        Node* target_node = nullptr;

        float elapsed_time = 0.0f;
        float switch_animation_ms = 0.08f;
        int animation_offset = 0;

        virtual void start();
        virtual void stop();
        void move(float delta_time);

        bool nodeOvershoot() const;
        Node* getNewTarget() const;

    public:
        Entity(Node* start_node, const sf::Texture& texture, float speed);

        void setTextureOffset(int x_off, int y_off);

        virtual void update(float delta_time) = 0;
};
