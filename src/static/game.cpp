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

    Player player(100, 100, 5.0f, player_texture);
    player.setScale(sprite_scale, sprite_scale);
    player.setTextureRect(sf::IntRect(0, 0, sprite_size, sprite_size));

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            player.setDirection(0, -1);
            player.setTextureRect(sf::IntRect(0, 3 * sprite_size, sprite_size, sprite_size));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            player.setDirection(0, 1);
            player.setTextureRect(sf::IntRect(0, sprite_size, sprite_size, sprite_size));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            player.setDirection(-1, 0);
            player.setTextureRect(sf::IntRect(0, 2 * sprite_size, sprite_size, sprite_size));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            player.setDirection(1, 0);
            player.setTextureRect(sf::IntRect(0, 0, sprite_size, sprite_size));
        }

        player.move();

        window.clear();
        window.draw(background);
        window.draw(player);
        window.display();
    }
}
