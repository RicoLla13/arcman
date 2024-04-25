#include "entity.h"

Entity::Entity(const sf::Vector2f& position, const sf::Vector2f& grid_position, sf::Texture& texture) :
    sf::Sprite(texture), grid_position(grid_position) {
        this->setPosition(position);
    }

void Entity::setTextureOffset(int x_off, int y_off, int size) {
    setTextureRect(sf::IntRect(x_off * size, y_off * size, size, size));
}
