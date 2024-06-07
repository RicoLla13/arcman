#include "entity.hpp"

Entity::Entity(const sf::Texture& texture) 
    : sf::Sprite(texture) {}

void Entity::setTextureOffset(int x_off, int y_off) {
    setTextureRect(sf::IntRect(x_off * sprite_size, y_off * sprite_size, sprite_size, sprite_size));
}
