#include "moving_entity.h"

MovingEntity::MovingEntity(const sf::Vector2f& grid_position, float velocity, const sf::Texture& texture) : 
    Entity(grid_position, texture), velocity(velocity), speed(0, 0) {}

void MovingEntity::move(float delta_time) {
    sf::Sprite::move(speed * delta_time);
}

void MovingEntity::setDirection(int x_dir, int y_dir) {
    this->speed.x = velocity * x_dir;
    this->speed.y = velocity * y_dir;
}

bool MovingEntity::isColliding(int e_x, int e_y, std::vector<std::vector<Tile*>>& grid) {
    bool output = false;

    float cell_x = e_x / static_cast<float>(rect_size);
    float cell_y = e_y / static_cast<float>(rect_size);

    for(int i = 0; i < 4; i++) {
        int x = 0;
        int y = 0;

        switch(i) {
            case 0:
                x = static_cast<int>(floor(cell_x));
                y = static_cast<int>(floor(cell_y));
                break;
            case 1:
                x = static_cast<int>(ceil(cell_x));
                y = static_cast<int>(floor(cell_y));
                break;
            case 2:
                x = static_cast<int>(floor(cell_x));
                y = static_cast<int>(ceil(cell_y));
                break;
            case 3:
                x = static_cast<int>(ceil(cell_x));
                y = static_cast<int>(ceil(cell_y));
                break;
        }

        if(x >= 0 && x < tile_grid_width && y >= 0 && y < tile_grid_height) {
            if(grid[y][x]->isSolid())
                output = true;
        }
    }

    return output;
}

