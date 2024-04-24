#include "entity.h"

Entity::Entity(int x_pos, int y_pos, sf::Texture& texture) :
    sf::Sprite(texture) {
        this->setPosition(x_pos, y_pos);
    }
