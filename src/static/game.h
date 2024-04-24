#ifndef GAME_H
#define GAME_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <string>

class Game {
    private:
        int window_width = 800;
        int window_height = 600;
        int frame_rate = 60;
        std::string window_title = "ARCMAN";

        Game();
        ~Game();

    public:
        sf::RenderWindow window;

        static Game& getInstance();

        Game(Game const&) = delete;
        void operator=(Game const&) = delete;

        void gameLoop();
};

#endif
