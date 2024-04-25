#include "player.h"
#include "../exception/custom_exception.h"

Player::Player(const sf::Vector2f& grid_position, float velocity, const sf::Texture& texture, int size) : 
    MovingEntity(grid_position, velocity, texture, size), score(0) {
        this->speed.x = velocity;
    }
