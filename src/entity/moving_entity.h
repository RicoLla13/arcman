#ifndef MOVING_ENTITY_CLASS
#define MOVING_ENTITY_CLASS

#include "entity.h"

class MovingEntity : public Entity {
    protected:
        float velocity;
        int x_speed;
        int y_speed;

    public:
        MovingEntity(int x_pos, int y_pos, float velocity, sf::Texture& texture);
        virtual ~MovingEntity() {}
};

#endif
