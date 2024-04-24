#ifndef GAME_H
#define GAME_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <string>

class Game {
    private:
        const int sprite_scale = 3;
        const int sprite_size = 16;

        int window_width = 15 * sprite_size * sprite_scale;
        int window_height = 18 * sprite_size * sprite_scale;
        int frame_rate = 60;
    
        std::string background_image = "assets/Level_1.png";

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
