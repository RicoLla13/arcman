#pragma once

#include "../global.hpp"
#include "../node/node.hpp"
#include "../entity/entity.hpp"
#include "../entity/moving/player.hpp"
#include "../entity/moving/ghost.hpp"
#include "../entity/static/static_entity.hpp"
#include "../entity/static/small_pellet.hpp"
#include "../entity/static/big_pellet.hpp"
#include "../exception/custom_exception.hpp"
#include "../logger/logger.hpp"

#include <SFML/Graphics.hpp>
#include <vector>
#include <array>
#include <cstdlib>
#include <string>
#include <iostream>

// The class that represents the game
// This class is a singleton, so only one instance of it can exist
class Game : public sf::RenderWindow {
    private:
        std::string window_title = "ARCMAN"; // Title of the window

        // Game Textures
        sf::Texture player_texture;
        sf::Texture ghost_texture;
        sf::Texture maze_texture;
        sf::Texture menu_texture;
        sf::Texture game_won_texture;
        sf::Texture game_over_texture;
        sf::Texture button_texture;
        sf::Texture numbers_texture;
        sf::Texture pellet_texture;

        float player_timer = 0; // The variable that manages the player's time 'score'

        // Booleans used to detect a key press
        bool w_was_pressed = false;   // W
        bool s_was_pressed = false;   // S
        bool ret_was_pressed = false; // Enter / Return
        
        sf::Clock clock; // SFML CLock used for timing (delta_time, score)
        Logger* logger;  // The logger object used to log messages

        // Singleton related
        static Game* instance; // current instance of the game
        Game();                // private constructor

        // Initialization functions
        void initNodes(std::vector<Node*>& nodes);
        void initPellets(std::array<std::array<StaticEntity*, tile_grid_width>, tile_grid_height>& pellets);
        void loadTextures();

        // Various helper functions
        void processNum(int num, sf::Sprite* sprite); // will process a digit into a sprite
        void checkPellets(Player* player, int& pellet_num, std::array<std::array<StaticEntity*, tile_grid_width>, tile_grid_height>& pellets); // Collision between the player and surrounding pellets

        // Main game functions
        bool handleEvent();   // Handle SFML events (mainly close window)
        GameState menu();     // The menu state
        GameState loop();     // The main game loop
        GameState gameOver(); // The game over state
        GameState gameWon();  // The game won state

    public:
        // Singleton related
        static Game* getInstance(); // returns the current instance of the game

        // Disallow copying
        Game(Game const&) = delete;
        void operator=(Game const&) = delete;
        // Destructor (only closes the window)
        ~Game();

        // Main game function (the state machine)
        void stateMachine();
};
