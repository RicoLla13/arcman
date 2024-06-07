#include "small_pellet.hpp"

SmallPellet::SmallPellet(const sf::Vector2f& position, const sf::Texture& texture)
    : StaticEntity(position, texture)
{
    this->setTextureOffset(1, 0);
    this->setScale(sf::Vector2f(sprite_scale, sprite_scale));
}
