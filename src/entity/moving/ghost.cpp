#include "ghost.hpp"

Ghost::Ghost(Node* start_node, const sf::Texture& texture, float speed, GhostName identifier)
    : MovingEntity(start_node, texture, speed), identifier(identifier)
{
    // Start with a random direction
    this->direction = this->getNewDirection();
    this->speed_norm = ghost_speed;
    // Get moving
    this->start();
}

// Compute a random direction with the valid neighbors
Direction Ghost::getNewDirection() {
    std::vector<Direction> possible_directions;

    // Compute valid neighbors
    for(int i = 0; i < 4; i++) {
        if(this->current_node->getNeighbour(static_cast<Direction>(i)) != nullptr) {
            if(!isOppositeDirection(static_cast<Direction>(i), this->direction))
                possible_directions.push_back(static_cast<Direction>(i));
        }
    }

    // If no valid neighbors, return NONE
    if(possible_directions.size() == 0)
        return Direction::NONE;

    // Return a random direction
    int random_index = rand() % possible_directions.size();
    return possible_directions[random_index];
}

void Ghost::update(float delta_time) {
    // Get a valid target node
    this->target_node = this->getNewTarget();

    // Check if ghost is overshooting
    if(this->nodeOvershoot()) {
        if(this->current_node != this->target_node) {
            this->stop();
            this->setPosition(this->target_node->getPosition());

            this->current_node = this->target_node;
            this->direction = this->getNewDirection();
        }
    }

    // Check if ghost is moving and if the new direction is valid
    if(!this->is_moving) {
        if(this->current_node->getNeighbour(this->direction) != nullptr)
            this->start();
    }

    // Update animation timer
    elapsed_time += delta_time;
    if(elapsed_time - switch_animation_ms >= 0) {
        elapsed_time = 0.0f;
        animation_offset = !animation_offset;
    }

    // Update texture with direction and animation offsets
    this->setTextureOffset(static_cast<int>(identifier) * 2 + animation_offset, static_cast<int>(direction));

    this->move(delta_time);
}
