#include "entity.h"

Entity::Entity(const sf::Vector2f& grid_position, const sf::Texture& texture) :
    sf::Sprite(texture) {
        this->setPosition(grid_position);
    }

void Entity::setTextureOffset(int x_off, int y_off) {
    setTextureRect(sf::IntRect(x_off * sprite_size, y_off * sprite_size, sprite_size, sprite_size));
}
