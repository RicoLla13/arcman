#ifndef MOVING_ENTITY_CLASS
#define MOVING_ENTITY_CLASS

#include "entity.h"
#include <cmath>

class MovingEntity : public Entity {
    protected:
        float velocity;
        sf::Vector2f direction;

    public:
        MovingEntity(const sf::Vector2f& grid_position, float velocity, const sf::Texture& texture);
        void setDirection(Direction direction);
        void move(float delta_time);
        sf::Vector2f getDirection() const { return direction; }
        virtual ~MovingEntity() {}
};

#endif
