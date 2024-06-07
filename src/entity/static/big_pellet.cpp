#include "big_pellet.hpp"

BigPellet::BigPellet(const sf::Vector2f& position, const sf::Texture& texture)
    : StaticEntity(position, texture)
{
    this->setTextureOffset(0, 0);
    this->setScale(sf::Vector2f(sprite_scale, sprite_scale));
}
