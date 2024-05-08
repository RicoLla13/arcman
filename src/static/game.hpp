#ifndef GAME
#define GAME

#include "../global.hpp"

#include "../node/node.hpp"

#include "../exception/custom_exception.hpp"

#include <SFML/Graphics.hpp>
#include <string>
#include <array>
#include <math.h>
#include <queue>

class Game : public sf::RenderWindow {
    private:
        std::string window_title = "ARCMAN";

        sf::Texture player_texture;

        Game();
        ~Game();

    public:
        static Game& getInstance();

        Game(Game const&) = delete;
        void operator=(Game const&) = delete;

        void gameLoop();
        void loadTextures();
};

#endif
