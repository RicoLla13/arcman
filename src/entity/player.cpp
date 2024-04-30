#include "player.h"
#include "../exception/custom_exception.h"

Player::Player(const sf::Vector2f& grid_position, float velocity, const sf::Texture& texture) : 
    MovingEntity(grid_position, velocity, texture), score(0) {
        this->speed.x = velocity;
    }

void Player::update(float delta_time, std::vector<std::vector<Tile*>> grid) {
    std::array<bool, 4> collision{};
    collision[0] = this->isColliding(getPosition().x + rect_size, getPosition().y, grid);
    collision[1] = this->isColliding(getPosition().x, getPosition().y - rect_size, grid);
    collision[2] = this->isColliding(getPosition().x - rect_size, getPosition().y, grid);
    collision[3] = this->isColliding(getPosition().x, getPosition().y + rect_size, grid);

    elapsed_time += delta_time;
    if(elapsed_time >= anim_interval) {
        anim_offset = !anim_offset;
        elapsed_time = 0.0f;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        if(!collision[1]) {
            direction = 1;
            dir_offset = 3;
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        if(!collision[3]) {
            direction = 3;
            dir_offset = 1;
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        if(!collision[2]) {
            direction = 2;
            dir_offset = 2;
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        if(!collision[0]) {
            direction = 0;
            dir_offset = 0;
        }
    }

    if(!collision[direction]) {
        switch(direction) {
            case 0:
                this->setDirection(1, 0);
                break;
            case 1:
                this->setDirection(0, -1);
                break;
            case 2:
                this->setDirection(-1, 0);
                break;
            case 3:
                this->setDirection(0, 1);
                break;
        }
            
    }

    this->setTextureOffset(anim_offset, dir_offset);
    this->move(delta_time);
}
