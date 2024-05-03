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

bool Game::isPlayerCollidingTile(MovingEntity& player) {
    sf::FloatRect player_bounds = player.getGlobalBounds();

    int start_x = std::max(0, static_cast<int>((player_bounds.left - (rect_size - 1)) / rect_size));
    int start_y = std::max(0, static_cast<int>((player_bounds.top - (rect_size - 1)) / rect_size));
    int end_x = std::min(tile_grid_width, static_cast<int>((player_bounds.left + player_bounds.width + (rect_size - 1)) / rect_size));
    int end_y = std::min(tile_grid_height, static_cast<int>((player_bounds.top + player_bounds.height + (rect_size - 1)) / rect_size));

    for(int i = start_y; i < end_y; i++) {
        for(int j = start_x; j < end_x; j++) {
            if(grid[i][j]->isSolid()) {
                sf::FloatRect tile_bounds = grid[i][j]->getGlobalBounds();

                tile_bounds.left -= 1.0f;
                tile_bounds.top -= 1.0f;
                tile_bounds.width -= 2.0f;
                tile_bounds.height -= 2.0f;

                if(player_bounds.intersects(tile_bounds))
                    return true;
            }
        }
    }

    return false;
}

void Game::gameLoop() {
    MovingEntity player(sf::Vector2f(1.0f * rect_size, 1.0f * rect_size), 300.0f, player_texture);
    player.setScale(sprite_scale, sprite_scale);
    player.setTextureRect(sf::IntRect(0, 0, sprite_size, sprite_size));
    
    float delta_time = 0.0f;
    float player_anim_time = 0.0f;
    float player_anim_speed = 0.1f;
    short player_anim = 0;
    short player_anim_dir = 0;

    while (this->isOpen()) {
        // window event handling
        sf::Event event;
        while (this->pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                this->close();
        }

        // compute delta time of each frame, using the clock
        delta_time = clock.restart().asSeconds();

        // manage if player mouth is open or closed, using the defined timers
        player_anim_time += delta_time;
        if(player_anim_time >= player_anim_speed) {
            player_anim_time = 0.0f;
            player_anim = !player_anim;
        }

        // manage player direction, and sprite direction
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            player.setDirection(Direction::UP);
            player_anim_dir = 0;
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            player.setDirection(Direction::DOWN);
            player_anim_dir = 1;
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            player.setDirection(Direction::LEFT);
            player_anim_dir = 2;
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            player.setDirection(Direction::RIGHT);
            player_anim_dir = 3;
        }

        // update sprite and move player
        player.setTextureRect(sf::IntRect(player_anim * sprite_size, player_anim_dir * sprite_size, sprite_size, sprite_size));
        player.move(delta_time);

        // check if player is colliding with a tile
        if(isPlayerCollidingTile(player))
            player.move(-delta_time);

        // check if player is out of bounds
        // if so, teleport player to other side of the screen
        sf::Vector2f player_pos = player.getPosition();
        if(player_pos.x < -rect_size)
            player.setPosition(window_width + rect_size, player_pos.y);
        else if(player_pos.x > window_width + rect_size)
            player.setPosition(-rect_size, player_pos.y);
        else if(player_pos.y < -rect_size)
            player.setPosition(player_pos.x, window_height + rect_size);
        else if(player_pos.y > window_height + rect_size)
            player.setPosition(player_pos.x, -rect_size);

        // clear window
        this->clear();

        // draw tile grid on window
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
