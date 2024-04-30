#include "tile.h"

Tile::Tile(const sf::Vector2f& grid_position, const sf::Texture& texture, bool isSolid) : 
    Entity(grid_position, texture), solid(isSolid) {}

Tile::Tile(const sf::Vector2f& grid_position, const sf::Texture& texture) : 
    Entity(grid_position, texture), solid(false) {}
