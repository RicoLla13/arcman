#pragma once

#include <string>
#include <cstdint>

constexpr int frame_rate = 60;
constexpr float sprite_scale = 3;
constexpr int sprite_size = 16;
constexpr int rect_size = static_cast<int8_t>(sprite_size * sprite_scale);

constexpr int tile_grid_width = 15;
constexpr int tile_grid_height = 18;

constexpr int window_width = tile_grid_width * sprite_size * sprite_scale;
constexpr int window_height = tile_grid_height * sprite_size * sprite_scale;

enum class Direction {
    UP = 0,
    DOWN = 1,
    LEFT = 2,
    RIGHT = 3,
    NONE = -1
};

bool isOppositeDirection(const Direction& d1, const Direction& d2);
