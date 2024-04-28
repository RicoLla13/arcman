#include "tile.h"

Tile::Tile(const sf::Vector2f& grid_position, const sf::Texture& texture, int size, bool isSolid) : 
    Entity(grid_position, texture, size), solid(isSolid) {}
