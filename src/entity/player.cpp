#include "player.h"
#include "../exception/custom_exception.h"

Player::Player(const sf::Vector2f& grid_position, float velocity, const sf::Texture& texture) : 
    MovingEntity(grid_position, velocity, texture), score(0) {
        this->speed.x = velocity;
    }

void Player::update(float delta_time) {
    elapsed_time += delta_time;
    if(elapsed_time >= anim_interval) {
        anim_offset = !anim_offset;
        elapsed_time = 0.0f;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        speed.x = 0;
        speed.y = -velocity;
        dir_offset = 3;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        speed.x = 0;
        speed.y = velocity;
        dir_offset = 1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        speed.x = -velocity;
        speed.y = 0;
        dir_offset = 2;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        speed.x = velocity;
        speed.y = 0;
        dir_offset = 0;
    }

    this->setTextureOffset(anim_offset, dir_offset);
    this->move(delta_time);
}
