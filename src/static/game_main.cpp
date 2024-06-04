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

void Game::state_machine() {
    bool stop = false;
    while(!stop) {
        switch(this->current_state) {
            case GameState::INIT:
                try {
                    this->loadTextures();
                } catch(CustomException& e) {
                    std::cerr << e.what() << std::endl;
                    return;
                }
                this->setupTestNodes();
                current_state = GameState::MENU;
                break;
            case GameState::MENU:
                current_state = this->menu();
                break;
            case GameState::RUN:
                this->loop();
                current_state = GameState::CLOSE;
                break;
            case GameState::GAME_OVER:
                this->gameOver();
                break;
            default:
                stop = true;
                break;
        }
    }
}

bool Game::handleEvent() {
    sf::Event event;
    while (this->pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            return true;
    }

    return false;
}

void Game::loadTextures() {
    if(!ghost_texture.loadFromFile("assets/Ghosts.png"))
        throw CustomException("[!] #loadTextures()# -> Ghost image not found!");
    if(!player_texture.loadFromFile("assets/Player.png"))
        throw CustomException("[!] #loadTextures()# -> Player image not found!");
    if(!maze_texture.loadFromFile("assets/Level_1.png"))
        throw CustomException("[!] #loadTextures()# -> Level 1 image not found!");
    if(!menu_texture.loadFromFile("assets/Menu.png"))
        throw CustomException("[!] #loadTextures()# -> Menu image not found!");
    if(!button_texture.loadFromFile("assets/Buttons.png"))
        throw CustomException("[!] #loadTextures()# -> Menu image not found!");
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

GameState Game::menu() {
    sf::Sprite background(menu_texture);
    background.setScale(sprite_scale, sprite_scale);

    sf::Sprite button_play(button_texture);
    button_play.setScale(sprite_scale, sprite_scale);
    button_play.setTextureRect(sf::IntRect(0, sprite_size, 5 * sprite_size , sprite_size));
    button_play.setPosition(5 * rect_size, 8 * rect_size);

    sf::Sprite button_exit(button_texture);
    button_exit.setScale(sprite_scale, sprite_scale);
    button_exit.setTextureRect(sf::IntRect(0, 2 * sprite_size, 5 * sprite_size , sprite_size));
    button_exit.setPosition(5 * rect_size, 10 * rect_size);

    bool selection = true;
    while(this->isOpen()) {
        if(this->handleEvent())
            break;

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            selection = true;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            selection = false;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
            if(selection)
                return GameState::RUN;
            else
                break;
        }

        if(selection) {
            button_play.setTextureRect(sf::IntRect(0, sprite_size, 5 * sprite_size , sprite_size));
            button_exit.setTextureRect(sf::IntRect(0, 2 * sprite_size, 5 * sprite_size , sprite_size));
        }
        else {
            button_play.setTextureRect(sf::IntRect(0, 0, 5 * sprite_size , sprite_size));
            button_exit.setTextureRect(sf::IntRect(0, 3 * sprite_size, 5 * sprite_size , sprite_size));
        }
        
        this->clear();
        this->draw(background);
        this->draw(button_play);
        this->draw(button_exit);
        this->display();
    }

    return GameState::CLOSE;
}

void Game::loop() {
    sf::Sprite background(maze_texture);
    background.setScale(sprite_scale, sprite_scale);

    Player player(nodes[0], player_texture, player_speed);
    player.setScale(sprite_scale, sprite_scale);
    player.setTextureOffset(0, 3);

    Ghost python(sf::Vector2f(rect_size * 6, rect_size * 10), ghost_texture, ghost_speed);
    python.setScale(sprite_scale, sprite_scale);
    python.setTextureOffset(0, 4);

    Ghost c_ghost(sf::Vector2f(rect_size * 7, rect_size * 10), ghost_texture, ghost_speed);
    c_ghost.setScale(sprite_scale, sprite_scale);
    c_ghost.setTextureOffset(2, 4);

    Ghost vhdl(sf::Vector2f(rect_size * 8, rect_size * 10), ghost_texture, ghost_speed);
    vhdl.setScale(sprite_scale, sprite_scale);
    vhdl.setTextureOffset(4, 4);

    float delta_time = 0.0f;

    while (this->isOpen()) {
        if(this->handleEvent())
            break;

        // calculate delta time
        delta_time = clock.restart().asSeconds();

        player.update(delta_time);

        // clear window
        this->clear();

        this->draw(background);

        // this->drawNodes();

        this->draw(player);

        this->draw(python);
        this->draw(c_ghost);
        this->draw(vhdl);

        this->display();
    }
}

void Game::gameOver() {}
