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

void Game::setupTestNodes() {
    // define some test nodes
    nodes.push_back(new Node(1 * rect_size, 2 * rect_size)); // node A
    nodes.push_back(new Node(4 * rect_size, 2 * rect_size)); // node B
    nodes.push_back(new Node(1 * rect_size, 4 * rect_size)); // node C
    nodes.push_back(new Node(4 * rect_size, 4 * rect_size)); // node D
    nodes.push_back(new Node(6 * rect_size, 4 * rect_size)); // node E
    nodes.push_back(new Node(1 * rect_size, 7 * rect_size)); // node F
    nodes.push_back(new Node(6 * rect_size, 7 * rect_size)); // node G

    // define node connections
    // node A
    nodes[0]->setNeighbour(Direction::RIGHT, nodes[1]); // A -> B
    nodes[0]->setNeighbour(Direction::DOWN, nodes[2]); // A -> C
    // node B
    nodes[1]->setNeighbour(Direction::LEFT, nodes[0]); // B -> A
    nodes[1]->setNeighbour(Direction::DOWN, nodes[3]); // B -> D
    // node C
    nodes[2]->setNeighbour(Direction::UP, nodes[0]); // C -> A
    nodes[2]->setNeighbour(Direction::RIGHT, nodes[3]); // C -> D
    nodes[2]->setNeighbour(Direction::DOWN, nodes[5]); // C -> F
    // node D
    nodes[3]->setNeighbour(Direction::UP, nodes[1]); // D -> B
    nodes[3]->setNeighbour(Direction::LEFT, nodes[2]); // D -> C
    nodes[3]->setNeighbour(Direction::RIGHT, nodes[4]); // D -> E
    // node E
    nodes[4]->setNeighbour(Direction::LEFT, nodes[3]); // E -> D
    nodes[4]->setNeighbour(Direction::DOWN, nodes[6]); // E -> G
    // node F
    nodes[5]->setNeighbour(Direction::UP, nodes[2]); // F -> C
    nodes[5]->setNeighbour(Direction::RIGHT, nodes[6]); // F -> G
    // node G
    nodes[6]->setNeighbour(Direction::UP, nodes[4]); // G -> E
    nodes[6]->setNeighbour(Direction::LEFT, nodes[5]); // G -> F
}

void Game::gameLoop() {
    Player player(nodes[0], player_texture, 200.0f);
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

        this->drawNodes();

        this->draw(player);

        this->display();
    }
}
