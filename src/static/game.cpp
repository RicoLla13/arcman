#include "game.h"

#include <iostream>

Game::Game() {
    this->create(sf::VideoMode(window_width, window_height), window_title);
    this->setFramerateLimit(frame_rate);
}

Game::~Game() {
    this->close();
}

Game& Game::getInstance() {
    static Game instance;
    return instance;
}

void Game::loadTextures() {
    if(!tile_texture.loadFromFile("assets/Debug_Tile.png"))
        throw CustomException("[!] #loadTextures()# -> Tile image not found!");
    if(!player_texture.loadFromFile("assets/Player.png"))
        throw CustomException("[!] #loadTextures()# -> Player image not found!");
}

void Game::convertMap(std::array<std::string, tile_grid_height> map) {
    for(int i = 0; i < tile_grid_height; i++) {
        std::vector<Tile*> row;

        for(int j = 0; j < tile_grid_width; j++) {
            Tile* tile = new Tile(sf::Vector2f(j * rect_size, i * rect_size));

            if(map[i][j] == '#') {
                tile->setTexture(tile_texture);
                tile->setSolid(true);
            }
            else
                tile->setSolid(false);

            tile->setScale(sprite_scale, sprite_scale);
            tile->setTextureRect(sf::IntRect(0, 0, sprite_size, sprite_size));
            row.push_back(tile);
        }

        grid.push_back(row);
    }
}

void Game::gameLoop() {
    Player player(sf::Vector2f(1.0f * rect_size, 3.0f * rect_size), 300.0f, player_texture);
    player.setScale(sprite_scale, sprite_scale);
    player.setTextureRect(sf::IntRect(0, 0, sprite_size, sprite_size));
    
    float delta_time = 0.0f;

    while (this->isOpen()) {
        sf::Event event;
        while (this->pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                this->close();
        }

        delta_time = clock.restart().asSeconds();

        player.update(delta_time);

        this->clear();

        for(auto& row : grid) {
            for(auto& tile : row)
            this->draw(*tile);
        }

        this->draw(player);
        this->display();
    }
    
    // free memory
    for(auto& row : grid) {
        for(auto& tile : row)
            delete tile;
    }
}
