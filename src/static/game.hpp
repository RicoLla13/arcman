#pragma once

#include "../global.hpp"
#include "../node/node.hpp"
#include "../entity/entity.hpp"
#include "../entity/moving/player.hpp"
#include "../entity/moving/ghost.hpp"
#include "../entity/static/static_entity.hpp"
#include "../entity/static/small_pellet.hpp"
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
        sf::Texture game_over_texture;
        sf::Texture button_texture;
        sf::Texture numbers_texture;
        sf::Texture pellet_texture;

        std::vector<Node*> nodes;
        std::vector<Ghost*> ghosts;
        std::vector<sf::Sprite*> timer;
        std::vector<StaticEntity*> pellets;
        sf::Sprite background;
        
        sf::Clock clock;
        GameState current_state = GameState::INIT;

        Game();

        void initNodes();
        void loadTextures();

        void drawNodes();
        void processNum(int num, sf::Sprite* sprite);

        bool handleEvent();
        GameState menu();
        void loop();
        void gameOver();

    public:
        static Game& getInstance();

        Game(Game const&) = delete;
        void operator=(Game const&) = delete;
        ~Game();

        void stateMachine();
};
