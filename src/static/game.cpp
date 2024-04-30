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

void Game::convertMap(std::array<std::string, tile_grid_height> map) {
    sf::Texture tile_texture;
    if(!tile_texture.loadFromFile("assets/Debug_Tile.png"))
        throw CustomException("[!] #Game()# -> Tile image not found!");

    for (int i = 0; i < tile_grid_height; ++i) {
        // Loop through each character in the string
        for (int j = 0; j < tile_grid_width; ++j) {
            grid[j][i] = new Tile(sf::Vector2f(j * rect_size, i * rect_size), tile_texture);

            if(map[i][j] == '#')
                grid[j][i]->setSolid(true);
            else if(map[i][j] == ' ') {
                grid[j][i]->setSolid(false);
                grid[j][i]->setTexture(sf::Texture());
            }

            grid[j][i]->setScale(sprite_scale, sprite_scale);

            std::cout << map[i][j];
        }
        std::cout << std::endl;
    }
}

void Game::gameLoop() {

    sf::Texture player_texture;
    if(!player_texture.loadFromFile("assets/Player.png"))
        throw CustomException("[!] #gameLoop()# -> Player image not found!");

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



        this->draw(player);
        this->display();
    }
    
    // free memory
    for(auto& row : grid) {
        for(auto& tile : row)
            delete tile;
    }
}
