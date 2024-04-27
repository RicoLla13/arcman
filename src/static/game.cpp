#include "game.h"

#include <iostream>

Game::Game() { 
    window.create(sf::VideoMode(window_width, window_height), window_title);
    window.setFramerateLimit(frame_rate);
}

Game::~Game() {
    window.close();
}

Game& Game::getInstance() {
    static Game instance;
    return instance;
}

bool Game::checkPlayerCollision(Player& player, int p_x_dir, int p_y_dir) {
    sf::Vector2f position = player.getPosition();
    sf::Vector2f speed = player.getSpeed();

    std::array<Tile*, 4> collision{};
    collision[0] = grid[floor(position.x / static_cast<float>(rect_size))][floor(position.y / static_cast<float>(rect_size))];
    collision[1] = grid[ceil(position.x / static_cast<float>(rect_size))][ceil(position.y / static_cast<float>(rect_size))];
    collision[2] = grid[ceil(position.x / static_cast<float>(rect_size))][floor(position.y / static_cast<float>(rect_size))];
    collision[3] = grid[floor(position.x / static_cast<float>(rect_size))][ceil(position.y / static_cast<float>(rect_size))];
    
    for(auto& col : collision) {
        if(col->isTileSolid())
            return true;
    }

    return false;
}

void Game::gameLoop() {
    /*
    sf::Texture background_texture;
    if(!background_texture.loadFromFile(background_image))
        throw CustomException("[!] #gameLoop()# -> Background image not found!");

    sf::Sprite background(background_texture);
    background.setScale(sprite_scale, sprite_scale);
    */

    sf::Texture tile_texture;
    if(!tile_texture.loadFromFile("assets/Debug_Tile.png"))
        throw CustomException("[!] #Game()# -> Tile image not found!");

    grid.reserve(15);
    for(int i = 0; i< 15; i++) {
        std::vector<Tile*> row;

        row.reserve(18);
        for(int j = 0; j < 18; j++) {
            if((j < 3 || j > 15) || (i < 1 || i > 13))
                row.push_back(new Tile(sf::Vector2f(i * rect_size, j * rect_size), tile_texture, sprite_size * sprite_scale, true));
            else
                row.push_back(new Tile(sf::Vector2f(i * rect_size, j * rect_size), sf::Texture(), sprite_size * sprite_scale, false));
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

    Player player(sf::Vector2f(1.0f * rect_size, 3.0f * rect_size), 5.0f, player_texture, rect_size);
    player.setScale(sprite_scale, sprite_scale);
    player.setTextureRect(sf::IntRect(0, 0, sprite_size, sprite_size));
    
    float delta_time = 0.0f;
    float elapsed_time = 0.0f;
    const float pl_anim_interval = 0.1f;
    struct {
        int anim = 0;
        int dir = 0;
    } player_texture_offset;
    int selected_dir = 3;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        delta_time = clock.restart().asSeconds();
        elapsed_time += delta_time;

        if(elapsed_time >= pl_anim_interval) {
            player_texture_offset.anim = !player_texture_offset.anim;
            elapsed_time = 0.0f;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) 
            selected_dir = 0;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) 
            selected_dir = 1;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            selected_dir = 2;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            selected_dir = 3;

        sf::Vector2f player_pos = player.getPosition();

        if(player_pos.x + rect_size < 0)
            player.setPosition(window_width, player_pos.y);
        else if(player_pos.x > window_width)
            player.setPosition(-rect_size, player_pos.y);
        else if(player_pos.y + rect_size < 0)
            player.setPosition(player_pos.x, window_height);
        else if(player_pos.y > window_height)
            player.setPosition(player_pos.x, -rect_size);

        int p_x_dir;
        int p_y_dir;

        switch(selected_dir) {
            case 0:
                p_x_dir = 0;
                p_y_dir = -1;
                player_texture_offset.dir = 3;
                break;
            case 1:
                p_x_dir = 0;
                p_y_dir = 1;
                player_texture_offset.dir = 1;
                break;
            case 2:
                p_x_dir = -1;
                p_y_dir = 0;
                player_texture_offset.dir = 2;
                break;
            case 3:
                p_x_dir = 1;
                p_y_dir = 0;
                player_texture_offset.dir = 0;
                break;
            default:
                p_x_dir = 0;
                p_y_dir = 0;
                break;
        }

        if(checkPlayerCollision(player, p_x_dir, p_y_dir)) {
            p_x_dir = 0;
            p_y_dir = 0;
        }
        player.setDirection(p_x_dir, p_y_dir);

        player.setTextureOffset(player_texture_offset.anim, player_texture_offset.dir, sprite_size);

        // debug -> freeze player
        // player.setDirection(0, 0);

        player.move();

        window.clear();
        // window.draw(background);

        for(auto& row : grid) {
            for(auto& tile : row)
            window.draw(*tile);
        }

        window.draw(player);
        window.display();
    }
    
    // free memory
    for(auto& row : grid) {
        for(auto& tile : row)
            delete tile;

        row.clear();
    }
    grid.clear();
}
