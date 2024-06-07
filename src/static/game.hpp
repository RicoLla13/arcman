#pragma once

#include "../global.hpp"
#include "../node/node.hpp"
#include "../entity/entity.hpp"
#include "../entity/player.hpp"
#include "../entity/ghost.hpp"
#include "../exception/custom_exception.hpp"

#include <SFML/Graphics.hpp>
#include <vector>

class Game : public sf::RenderWindow {
    private:
        std::string window_title = "ARCMAN";

        sf::Texture player_texture;
        sf::Texture ghost_texture;
        sf::Texture maze_texture;
        sf::Texture menu_texture;
        sf::Texture button_texture;
        std::vector<Node*> nodes;
        
        sf::Clock clock;

        GameState current_state = GameState::INIT;

        Game();

        void drawNodes();
        void setupTestNodes();
        bool handleEvent();
        GameState menu();
        void loop();
        void gameOver();
        void loadTextures();

    public:
        static Game& getInstance();

        Game(Game const&) = delete;
        void operator=(Game const&) = delete;
        ~Game();

        void stateMachine();
};
