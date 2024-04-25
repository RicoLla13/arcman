#include "player.h"
#include "../exception/custom_exception.h"

Player::Player(const sf::Vector2f& position, const sf::Vector2f& grid_position, float velocity, sf::Texture& texture) : 
    MovingEntity(position, grid_position, velocity, texture), score(0) {
        this->speed.x = velocity;
    }
