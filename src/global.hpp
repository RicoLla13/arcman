#pragma once

#include <string>
#include <cstdint>

/* 
 * All the general constants that i will use in the game
 * ## sprite_scale     ## -> the mutiplier that the sprite will have compared to the base sprite
 * ## sprite_size      ## -> the size of the base sprite in pixels
 * ## rect_size        ## -> the size of the sprite after the scale
 * ## tile_grid_width  ## -> the number of rectangles the window will contain, horizontally
 * ## tile_grid_height ## -> the number of rectangles the window will contain, vertically
 * ## window_width     ## -> the width of the window in pixels
 * ## window_height    ## -> the height of the window in pixels
 */
constexpr int frame_rate = 60;
constexpr float sprite_scale = 3;
constexpr int sprite_size = 16;
constexpr int rect_size = static_cast<int8_t>(sprite_size * sprite_scale);

constexpr int tile_grid_width = 15;
constexpr int tile_grid_height = 18;

constexpr int window_width = tile_grid_width * sprite_size * sprite_scale;
constexpr int window_height = tile_grid_height * sprite_size * sprite_scale;

/*
 * Enum that represents the direction of an entity
 * the numbers assigned will be used, for example, 
 * in computing the sprite rectangle from the sprite sheet, 
 * or define node neighbors
*/

enum class Direction {
    UP = 0,
    DOWN = 1,
    LEFT = 2,
    RIGHT = 3,
    NONE = -1
};

/* 
 * A funciton that checks if two provided directions are different,
 * used by various objects troughout the game
 */
bool isOppositeDirection(const Direction& d1, const Direction& d2);
