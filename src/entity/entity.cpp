#include "entity.h"

Entity::Entity(const sf::Vector2f& grid_position, const sf::Texture& texture, int size) :
    sf::Sprite(texture), sprite_size(size) {
        this->setPosition(grid_position);
    }

void Entity::setTextureOffset(int x_off, int y_off, int size) {
    setTextureRect(sf::IntRect(x_off * size, y_off * size, size, size));
}
