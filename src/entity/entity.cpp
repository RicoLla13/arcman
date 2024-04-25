#include "entity.h"

Entity::Entity(const sf::Vector2f& grid_position, const sf::Texture& texture, int size) :
    sf::Sprite(texture), grid_position(grid_position), sprite_size(size) {
        this->setPosition(grid_position.x * size, grid_position.y * size);
    }

void Entity::setTextureOffset(int x_off, int y_off, int size) {
    setTextureRect(sf::IntRect(x_off * size, y_off * size, size, size));
}

sf::Vector2f Entity::getGridPosition() const {
    return grid_position;
}
