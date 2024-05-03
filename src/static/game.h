#ifndef GAME_H
#define GAME_H

#include "../global.h"

#include "../entity/entity.h"
#include "../entity/tile.h"
#include "../entity/moving_entity.h"
#include "../exception/custom_exception.h"

#include <SFML/Graphics.hpp>
#include <string>
#include <array>
#include <math.h>

class Game : public sf::RenderWindow {
    private:
        std::string window_title = "ARCMAN";
        sf::Clock clock;
        std::vector<std::vector<Tile*>> grid;

        sf::Texture tile_texture;
        sf::Texture player_texture;

        Game();
        ~Game();

    public:
        static Game& getInstance();

        Game(Game const&) = delete;
        void operator=(Game const&) = delete;

        void gameLoop();
        void convertMap(std::array<std::string, tile_grid_height> map);
        void loadTextures();

        // entity related functions
        bool isPlayerCollidingTile(MovingEntity& player);
};

#endif
