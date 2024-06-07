#pragma once

#include "../entity.hpp"
#include "../../node/node.hpp"

class MovingEntity : public Entity {
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
        MovingEntity(Node* start_node, const sf::Texture& texture, float speed);

        virtual void update(float delta_time) = 0;
};
