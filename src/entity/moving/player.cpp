#include "player.hpp"

Player::Player(Node* start_node, const sf::Texture& texture, float speed) 
    : MovingEntity(start_node, texture, speed) 
{
    // Initialize with going right
    this->direction = Direction::RIGHT;
    // Init starting node
    this->target_node = this->current_node->getNeighbour(this->direction);
    // Get moving
    this->start();
}

Direction Player::getInput() {
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        return Direction::UP;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        return Direction::DOWN;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        return Direction::LEFT;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        return Direction::RIGHT;

    return this->direction;
}

bool Player::collideGhosts(const std::vector<Ghost*> ghosts) {
    for(const auto& ghost : ghosts) {
        sf::Vector2f ghost_position = ghost->getPosition();
        sf::Vector2f player_position = this->getPosition();

        // Check if player reduced hitbox collides with ghost reduced hitbox
        if(abs(ghost_position.x - player_position.x) < ghost_error &&
            abs(ghost_position.y - player_position.y) < ghost_error)
            return true;
    }

    return false;
}

bool Player::collide(StaticEntity* entity) {
    if(entity == nullptr)
        return false;
    if(entity->is_eaten)
        return false;
    
    sf::Vector2f entity_position = entity->getPosition();
    sf::Vector2f player_position = this->getPosition();

    // Check if player reduced hitbox collides with pellet reduced hitbox
    if(abs(entity_position.x - player_position.x) < eat_error &&
        abs(entity_position.y - player_position.y) < eat_error)
        return true;

    return false;
}

void Player::update(float delta_time) {
    // Get a new valid target node
    this->target_node = this->getNewTarget();

    // Begin local computing of directin
    Direction local_direction = this->getInput();

    // Check if player is overshooting target node
    if(this->nodeOvershoot()) {
        if(this->current_node != this->target_node) {
            this->stop();
            this->setPosition(this->target_node->getPosition());

            this->current_node = this->target_node;
            this->direction = local_direction;
        }
    }

    // Check if player is moving and if the new direction is valid
    if(!this->is_moving) {
        if(this->current_node->getNeighbour(local_direction) != nullptr) {
            this->direction = local_direction;
            this->start();
        }
    }

    // Check if player wants to move in the opposite direction
    if(isOppositeDirection(local_direction, this->direction)) {
        Node* tmp = this->current_node;
        this->current_node = this->target_node;
        this->target_node = tmp;

        this->direction = local_direction;
    }

    // Mouth animation timer
    this->elapsed_time += delta_time;
    if(this->elapsed_time - this->switch_animation_ms >= 0) {
        this->elapsed_time = 0.0f;
        this->animation_offset = !this->animation_offset;
    }

    // Update texture with direction and mouth animation offsets
    this->setTextureOffset(this->animation_offset, static_cast<int>(this->direction));

    this->move(delta_time);
}
