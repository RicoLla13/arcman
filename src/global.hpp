#pragma once

#include <SFML/Graphics.hpp>

// Graphic configuration constants
constexpr int frame_rate = 60; // Frame rate of the game
constexpr float sprite_scale = 3.5f; //the scale multiplier form the original sprite file
constexpr int sprite_size = 16; // the size in pixels of a sprite (all sprites are rectangles)
constexpr int rect_size = static_cast<int>(sprite_size * sprite_scale); // the size in pixels of a sprite after scaling

// The game canvas is organized abstractly as a grid of tiles
// The grid is 15 tiles wide and 18 tiles high
constexpr int tile_grid_width = 15;
constexpr int tile_grid_height = 18;

// Window parameters, calculated from the grid size and the sprite size
constexpr int window_width = tile_grid_width * sprite_size * sprite_scale;
constexpr int window_height = tile_grid_height * sprite_size * sprite_scale;

// Game parameters
constexpr float player_speed = 250.0f; // The speed of the player in pixels per second
constexpr float ghost_speed = 100.0f; // The speed of the ghosts in pixels per second
constexpr float eat_error = 5.0f; // The distance from the center of the tile that the player can eat a pellet
constexpr float ghost_error = 25.0f; // The distance from the center of the tile that the player can collide with a ghost
constexpr float big_pellet_bonus = 1.5f; // The time substracted when the player eats a big pellet

// Enums
// Directions an entity can move
enum class Direction {
    UP = 0,
    DOWN = 1,
    LEFT = 2,
    RIGHT = 3,
    NONE = -1 // Represents no movement
};

// The states of the game state machine
enum class GameState {
    CLOSE,    // Close the game
    INIT,     // Initialize the game
    MENU,     // The main menu
    RUN,      // The game is running (game loop)
    GAME_WON, // The player has won the game
    GAME_OVER // The player has lost the game
};

// This is used to identify each ghost, left here for future development
enum class GhostName {
    PYTHON = 0,
    C = 1,
    VHDL = 2
};

// Utility functions
// Used in various entities to check if 2 different directions are opposite from one another
bool isOppositeDirection(const Direction& d1, const Direction& d2);
