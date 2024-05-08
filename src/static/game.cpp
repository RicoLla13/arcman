#include "game.hpp"

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
    if(!player_texture.loadFromFile("assets/Player.png"))
        throw CustomException("[!] #loadTextures()# -> Player image not found!");
}

void Game::gameLoop() {
    std::vector<Node*> nodes;

    // create nodes
    for (int i = 0; i < 10; i++)
        nodes.push_back(new Node(sf::Vector2f(i * 100, 0)));

    while (this->isOpen()) {
        // window event handling
        sf::Event event;
        while (this->pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                this->close();
        }

        // clear window
        this->clear();

        // for each node draw a red circle with radius 20
        for(auto node : nodes) {
            sf::CircleShape circle(20);
            circle.setFillColor(sf::Color::Red);
            circle.setPosition(node->getPosition());
            this->draw(circle);
        }

        this->display();
    }

    // cleanup
    for(auto node : nodes)
        delete node;
}
