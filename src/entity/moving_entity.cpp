#include "moving_entity.h"

MovingEntity::MovingEntity(int x_pos, int y_pos, float velocity, sf::Texture& texture) : 
    Entity(x_pos, y_pos, texture), velocity(velocity), x_speed(velocity), y_speed(0) {}
