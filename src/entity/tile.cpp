#include "tile.h"

Tile::Tile(const sf::Vector2f& grid_position, const sf::Texture& texture, bool isSolid) : 
    Entity(grid_position, texture), solid(isSolid) {}
