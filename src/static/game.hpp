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

class Game : public sf::RenderWindow {
    private:
        std::string window_title = "ARCMAN";

        sf::Texture player_texture;
        sf::Texture ghost_texture;
        sf::Texture maze_texture;
        sf::Texture menu_texture;
        sf::Texture game_won_texture;
        sf::Texture game_over_texture;
        sf::Texture button_texture;
        sf::Texture numbers_texture;
        sf::Texture pellet_texture;

        std::vector<Node*> nodes;
        std::array<std::array<StaticEntity*, tile_grid_width>, tile_grid_height> pellets;

        float player_timer = 0;

        bool w_was_pressed = false;
        bool s_was_pressed = false;
        bool ret_was_pressed = false;
        
        sf::Clock clock;
        GameState current_state = GameState::INIT;

        Logger* logger;

        static Game* instance;
        Game();

        void initNodes();
        void clearNodes();
        void initPellets();
        void clearPellets();
        void loadTextures();

        void drawNodes();
        void processNum(int num, sf::Sprite* sprite);
        void checkPellets(Player* player, int& pellet_num);

        bool handleEvent();
        GameState menu();
        GameState loop();
        GameState gameOver();
        GameState gameWon();

    public:
        static Game* getInstance();

        Game(Game const&) = delete;
        void operator=(Game const&) = delete;
        ~Game();

        void stateMachine();
};
