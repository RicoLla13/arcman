#include "ghost.hpp"

Ghost::Ghost(Node* start_node, const sf::Texture& texture, float speed, GhostName identifier)
    : MovingEntity(start_node, texture, speed), identifier(identifier)
{
    this->direction = this->getNewDirection();
    this->speed_norm = ghost_speed;
    this->start();
}

Direction Ghost::getNewDirection() {
    std::vector<Direction> possible_directions;

    for(int i = 0; i < 4; i++) {
        if(this->current_node->getNeighbour(static_cast<Direction>(i)) != nullptr) {
            if(!isOppositeDirection(static_cast<Direction>(i), this->direction))
                possible_directions.push_back(static_cast<Direction>(i));
        }
    }

    if(possible_directions.size() == 0)
        return Direction::NONE;

    int random_index = rand() % possible_directions.size();
    return possible_directions[random_index];
}

void Ghost::update(float delta_time) {
    this->target_node = this->getNewTarget();

    if(this->nodeOvershoot()) {
        if(this->current_node != this->target_node) {
            this->stop();
            this->setPosition(this->target_node->getPosition());

            this->current_node = this->target_node;
            this->direction = this->getNewDirection();
        }
    }

    if(!this->is_moving) {
        if(this->current_node->getNeighbour(this->direction) != nullptr)
            this->start();
    }

    elapsed_time += delta_time;
    if(elapsed_time - switch_animation_ms >= 0) {
        elapsed_time = 0.0f;
        animation_offset = !animation_offset;
    }

    setTextureOffset(static_cast<int>(identifier) * 2 + animation_offset, static_cast<int>(direction));

    move(delta_time);
}
