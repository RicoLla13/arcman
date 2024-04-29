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

void Game::gameLoop() {
    // Debug Tile texture
    sf::Texture tile_texture;
    if(!tile_texture.loadFromFile("assets/Debug_Tile.png"))
        throw CustomException("[!] #Game()# -> Tile image not found!");

    grid.reserve(15);
    for(int i = 0; i< 15; i++) {
        std::vector<Tile*> row;

        row.reserve(18);
        for(int j = 0; j < 18; j++) {
            if((j < 3 || j > 15) || (i < 1 || i > 13))
                row.push_back(new Tile(sf::Vector2f(i * rect_size, j * rect_size), tile_texture, true));
            else
                row.push_back(new Tile(sf::Vector2f(i * rect_size, j * rect_size), sf::Texture(), false));
        }

        grid.push_back(std::move(row));
    }

    for(auto& row : grid) {
        for(auto& tile : row) {
            tile->setScale(sprite_scale, sprite_scale);
        }
    }

    sf::Texture player_texture;
    if(!player_texture.loadFromFile("assets/Player.png"))
        throw CustomException("[!] #gameLoop()# -> Player image not found!");

    Player player(sf::Vector2f(1.0f * rect_size, 3.0f * rect_size), 5.0f, player_texture);
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

        row.clear();
    }
    grid.clear();
}
