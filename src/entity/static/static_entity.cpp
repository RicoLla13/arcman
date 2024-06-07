#include "static_entity.hpp"

StaticEntity::StaticEntity(const sf::Vector2f& position, const sf::Texture& texture)
    : Entity(texture)
{
    this->setPosition(position);
}
