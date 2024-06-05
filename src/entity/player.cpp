#include "player.hpp"

Player::Player(Node* start_node, const sf::Texture& texture, float speed) 
    : Entity(start_node, texture, speed) 
{
    this->direction = Direction::RIGHT;
}

void Player::update(float delta_time) {
    elapsed_time += delta_time;
    if(elapsed_time - switch_animation_ms >= 0) {
        elapsed_time = 0.0f;
        animation_offset = !animation_offset;
    }

    setTextureOffset(animation_offset, static_cast<int>(direction));

    move(delta_time);
}
