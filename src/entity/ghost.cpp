#include "ghost.hpp"

Ghost::Ghost(Node* start_node, const sf::Texture& texture, float speed, int ghost_number) 
    : Entity(start_node, texture, speed), ghost_number(ghost_number)
{
    this->direction = Direction::RIGHT;
}

void Ghost::update(float delta_time) {
    elapsed_time += delta_time;
    if(elapsed_time - switch_animation_ms >= 0) {
        elapsed_time = 0.0f;
        animation_offset = !animation_offset;
    }

    setTextureOffset(ghost_number * 2 + animation_offset, static_cast<int>(direction));

    move(delta_time);
}
