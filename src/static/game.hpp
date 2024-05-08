#ifndef GAME
#define GAME

#include "../global.hpp"
#include "../node/node.hpp"
#include "../entity/entity.hpp"
#include "../entity/player.hpp"
#include "../exception/custom_exception.hpp"

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

class Game : public sf::RenderWindow {
    private:
        std::string window_title = "ARCMAN";

        sf::Texture player_texture;
        std::vector<Node*> nodes;
        
        sf::Clock clock;

        Game();

        void drawNodes();

    public:
        static Game& getInstance();

        Game(Game const&) = delete;
        void operator=(Game const&) = delete;
        ~Game();

        void setupTestNodes();
        void gameLoop();
        void loadTextures();
};

#endif
