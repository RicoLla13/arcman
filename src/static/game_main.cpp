#include "game.hpp"

#include <iostream>

Game::Game() {
    this->create(sf::VideoMode(window_width, window_height), window_title);
    this->setFramerateLimit(frame_rate);
}

Game::~Game() {
    this->close();

    for(auto node : nodes) {
        if(node != nullptr)
            delete node;

        node = nullptr;
    }

    std::cout << "[*] Game instance destroyed!" << std::endl;
}

Game& Game::getInstance() {
    static Game instance;
    return instance;
}

void Game::loadTextures() {
    if(!player_texture.loadFromFile("assets/Player.png"))
        throw CustomException("[!] #loadTextures()# -> Player image not found!");
    if(!background_texture.loadFromFile("assets/Level_1.png"))
        throw CustomException("[!] #loadTextures()# -> Level 1 image not found!");
}

void Game::drawNodes() {
    // for each node draw a red circle with radius 20
    for(auto node : nodes) {
        if(node == nullptr)
            throw CustomException("[!] #gameLoop()# -> A node in node vector is null!");

        sf::CircleShape circle(20);
        circle.setFillColor(sf::Color::Blue);
        circle.setPosition(node->getPosition());
        this->draw(circle);

        // draw connections
        for(auto neighbor : node->getAllNeighbours()) {
            if(neighbor == nullptr)
                continue;

            // Calculate the positions of the nodes
            sf::Vector2f startPos = node->getPosition() + sf::Vector2f(20, 20); // Start of the line (center of the node)
            sf::Vector2f endPos = neighbor->getPosition() + sf::Vector2f(20, 20); // End of the line (center of the connected node)

            // Create line vertices
            sf::Vertex line[] = {
                sf::Vertex(startPos),
                sf::Vertex(endPos)
            };

            // Draw the line
            this->draw(line, 2, sf::Lines);
        }
    }
}

void Game::gameLoop() {
    sf::Sprite background(background_texture);
    background.setScale(sprite_scale, sprite_scale);

    Player player(nodes[0], player_texture, 350.0f);
    player.setScale(sprite_scale, sprite_scale);
    player.setTextureOffset(0, 3);

    float delta_time = 0.0f;

    while (this->isOpen()) {
        // window event handling
        sf::Event event;
        while (this->pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                this->close();
        }

        // calculate delta time
        delta_time = clock.restart().asSeconds();

        player.update(delta_time);

        // clear window
        this->clear();

        this->draw(background);

        // this->drawNodes();

        this->draw(player);

        this->display();
    }
}
