#ifndef GLOBAL_H
#define GLOBAL_H

#include <string>

constexpr int frame_rate = 60;
constexpr int sprite_scale = 3;
constexpr int sprite_size = 16;
constexpr int rect_size = sprite_size * sprite_scale;

constexpr int tile_grid_width = 15;
constexpr int tile_grid_height = 18;

constexpr int window_width = tile_grid_width * sprite_size * sprite_scale;
constexpr int window_height = tile_grid_height * sprite_size * sprite_scale;

enum class Direction {
    UP,
    DOWN,
    LEFT,
    RIGHT,
    NONE
};

#endif
