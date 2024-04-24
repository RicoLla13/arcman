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

void Game::gameLoop() {
    sf::Texture texture;
    texture.loadFromFile("assets/Player.png");

    sf::Sprite sprite(texture);
    sprite.setScale(4, 4);

    int frame_count = 0;
    const int update_rate = 4;
    int hor_offset = 0;
    int ver_offset = 0;
    float movement_speed = 5.0f;
    float y_speed = 0.0f;
    float x_speed = movement_speed;
    sprite.setPosition(0, 0);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        frame_count++;
        if(frame_count >= frame_rate) 
            frame_count = 0;
        if(frame_count % 4 == 0)
            hor_offset++;
        if(hor_offset > 1)
            hor_offset = 0;

        // Handle keyboard input
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            y_speed = -movement_speed;
            x_speed = 0.0f;
            ver_offset = 3;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            y_speed = movement_speed;
            x_speed = 0.0f;
            ver_offset = 1;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            x_speed = -movement_speed;
            y_speed = 0.0f;
            ver_offset = 2;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            x_speed = movement_speed;
            y_speed = 0.0f;
            ver_offset = 0;
        }

        sprite.move(x_speed, y_speed);

        sprite.setTextureRect(sf::IntRect(hor_offset * 17 + 1, ver_offset * 17 + 1, 16, 16));

        window.clear();
        window.draw(sprite);
        window.display();
    }
}
