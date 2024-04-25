#ifndef MOVING_ENTITY_CLASS
#define MOVING_ENTITY_CLASS

#include "entity.h"

class MovingEntity : public Entity {
    protected:
        float velocity;
        sf::Vector2f speed;

    public:
        MovingEntity(const sf::Vector2f& grid_position, float velocity, const sf::Texture& texture, int size);
        void setDirection(int x_dir, int y_dir);
        void move();
        virtual ~MovingEntity() {}
};

#endif
