#include "tile.h"

Tile::Tile(const sf::Vector2f& position, const sf::Vector2f& grid_position, sf::Texture& texture, bool isSolid) : 
    Entity(position, grid_position, texture), isSolid(isSolid) {}
