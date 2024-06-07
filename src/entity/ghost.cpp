#include "ghost.hpp"

Ghost::Ghost(Node* start_node, const sf::Texture& texture, float speed, GhostName identifier)
    : Entity(start_node, texture, speed), identifier(identifier)
{
    this->direction = Direction::RIGHT;
}

void Ghost::update(float delta_time) {
    elapsed_time += delta_time;
    if(elapsed_time - switch_animation_ms >= 0) {
        elapsed_time = 0.0f;
        animation_offset = !animation_offset;
    }

    setTextureOffset(static_cast<int>(identifier) * 2 + animation_offset, static_cast<int>(direction));

    move(delta_time);
}
