#ifndef GAME_H
#define GAME_H

#include "../entity/entity.h"
#include "../entity/tile.h"
#include "../entity/player.h"
#include "../exception/custom_exception.h"

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <string>
#include <array>
#include <math.h>

class Game {
    private:
        const int frame_rate = 60;
        const int sprite_scale = 3;
        const int sprite_size = 16;
        const int rect_size = sprite_size * sprite_scale;

        int window_width = 15 * sprite_size * sprite_scale;
        int window_height = 18 * sprite_size * sprite_scale;

        std::string background_image = "assets/Level_1.png";
        std::string window_title = "ARCMAN";

        std::vector<std::vector<Tile*>> grid;

        Game();
        ~Game();

    public:
        sf::RenderWindow window;
        sf::Clock clock;
        static Game& getInstance();

        Game(Game const&) = delete;
        void operator=(Game const&) = delete;
        bool checkPlayerCollision(Player& player, int p_x_dir, int p_y_dir);

        void gameLoop();
};

#endif
