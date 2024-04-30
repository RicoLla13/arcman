#ifndef MOVING_ENTITY_CLASS
#define MOVING_ENTITY_CLASS

#include "entity.h"
#include "tile.h"
#include <cmath>

class MovingEntity : public Entity {
    protected:
        float velocity;
        int direction = 0;
        sf::Vector2f speed;

    public:
        MovingEntity(const sf::Vector2f& grid_position, float velocity, const sf::Texture& texture);
        void setDirection(int x_dir, int y_dir);
        void move(float delta_time);
        bool isColliding(int e_x, int e_y, std::vector<std::vector<Tile*>>& grid);
        sf::Vector2f getSpeed() const { return speed; }
        virtual ~MovingEntity() {}
};

#endif
