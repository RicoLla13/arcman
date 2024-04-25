#include "game.h"
#include "../entity/player.h"
#include "../exception/custom_exception.h"

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

void Game::gameLoop() {
    sf::Texture background_texture;
    if(!background_texture.loadFromFile(background_image))
        throw CustomException("[!] #gameLoop()# -> Background image not found!");

    sf::Sprite background(background_texture);
    background.setScale(sprite_scale, sprite_scale);

    sf::Texture player_texture;
    if(!player_texture.loadFromFile("assets/Player.png"))
        throw CustomException("[!] #gameLoop()# -> Player image not found!");

    Player player(sprite_size * sprite_scale, 4 * sprite_size * sprite_scale, 5.0f, player_texture);
    player.setScale(sprite_scale, sprite_scale);
    player.setTextureRect(sf::IntRect(0, 0, sprite_size, sprite_size));
    
    float delta_time = 0.0f;
    float elapsed_time = 0.0f;
    const float pl_anim_interval = 0.1f;
    struct {
        int anim = 0;
        int dir = 0;
    } player_texture_offset;
    int lastPlayerPosX = 0;
    int lastPlayerPosY = 0;
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
        int player_pos_x = static_cast<int>(player_pos.x);
        int player_pos_y = static_cast<int>(player_pos.y);

        if(player_pos_x + sprite_size * sprite_scale < 0)
            player.setPosition(window_width, player_pos_y);
        else if(player_pos_x > window_width)
            player.setPosition(-sprite_size * sprite_scale, player_pos_y);
        else if(player_pos_y + sprite_size * sprite_scale < 0)
            player.setPosition(player_pos_x, window_height);
        else if(player_pos_y > window_height)
            player.setPosition(player_pos_x, -sprite_size * sprite_scale);

        bool positionChangedX = player_pos_x % sprite_size == 0 && player_pos_x != lastPlayerPosX;
        bool positionChangedY = player_pos_y % sprite_size == 0 && player_pos_y != lastPlayerPosY;

        if (positionChangedX || positionChangedY) {
            if (positionChangedX && (selected_dir == 0 || selected_dir == 1)) {
                // Change Y direction only if moving vertically
                player.setDirection(0, selected_dir == 0 ? -1 : 1);
                player_texture_offset.dir = selected_dir == 0 ? 3 : 1;
            } else if (positionChangedY && (selected_dir == 2 || selected_dir == 3)) {
                // Change X direction only if moving horizontally
                player.setDirection(selected_dir == 2 ? -1 : 1, 0);
                player_texture_offset.dir = selected_dir == 2 ? 2 : 0;
            }
        }

        lastPlayerPosX = player_pos_x;
        lastPlayerPosY = player_pos_y;

        player.setTextureOffset(player_texture_offset.anim, player_texture_offset.dir, sprite_size);

        player.move();

        window.clear();
        window.draw(background);
        window.draw(player);
        window.display();
    }
}
