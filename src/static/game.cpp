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

    Player player(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(0.0f, 0.0f), 5.0f, player_texture);
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

        if(player_pos.x + sprite_size * sprite_scale < 0)
            player.setPosition(window_width, player_pos.y);
        else if(player_pos.x > window_width)
            player.setPosition(-sprite_size * sprite_scale, player_pos.y);
        else if(player_pos.y + sprite_size * sprite_scale < 0)
            player.setPosition(player_pos.x, window_height);
        else if(player_pos.y > window_height)
            player.setPosition(player_pos.x, -sprite_size * sprite_scale);

        switch(selected_dir) {
            case 0:
                player.setDirection(0, -1);
                player_texture_offset.dir = 3;
                break;
            case 1:
                player.setDirection(0, 1);
                player_texture_offset.dir = 1;
                break;
            case 2:
                player.setDirection(-1, 0);
                player_texture_offset.dir = 2;
                break;
            case 3:
                player.setDirection(1, 0);
                player_texture_offset.dir = 0;
                break;
        }

        player.setTextureOffset(player_texture_offset.anim, player_texture_offset.dir, sprite_size);

        player.move();

        window.clear();
        window.draw(background);
        window.draw(player);
        window.display();
    }
}
