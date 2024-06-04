#include "ghost.hpp"

Ghost::Ghost(const sf::Vector2f& grid_position, const sf::Texture& texture, float speed) :
    Entity(grid_position, texture, speed) {}
