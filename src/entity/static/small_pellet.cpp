#include "small_pellet.hpp"

SmallPellet::SmallPellet(const sf::Vector2f& position, const sf::Texture& texture)
    : StaticEntity(position, texture)
{
    this->setTextureOffset(1, 0);
}
