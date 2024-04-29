#ifndef GAME_H
#define GAME_H

#include "../entity/entity.h"
#include "../entity/tile.h"
#include "../entity/player.h"
#include "../exception/custom_exception.h"

#include <SFML/Graphics.hpp>
#include <string>
#include <array>
#include <math.h>

class Game : public sf::RenderWindow {
    private:
        const int frame_rate = 60;
        const int sprite_scale = 3;
        const int sprite_size = 16;
        const int rect_size = sprite_size * sprite_scale;

        int window_width = 15 * sprite_size * sprite_scale;
        int window_height = 18 * sprite_size * sprite_scale;

        std::string background_image = "assets/Level_1.png";
        std::string window_title = "ARCMAN";
        sf::Clock clock;

        std::vector<std::vector<Tile*>> grid;

        Game();
        ~Game();

    public:
        static Game& getInstance();

        Game(Game const&) = delete;
        void operator=(Game const&) = delete;

        void gameLoop();
};

#endif
