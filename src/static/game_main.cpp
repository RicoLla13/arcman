#include "game.hpp"

Game::Game() {
    this->create(sf::VideoMode(window_width, window_height), window_title);
    this->setFramerateLimit(frame_rate);
    srand(static_cast<unsigned int>(time(0)));
}

Game::~Game() {
    this->close();

    for(auto node : nodes) {
        if(node != nullptr)
            delete node;

        node = nullptr;
    }

    for(auto ghost : ghosts) {
        if(ghost != nullptr)
            delete ghost;
        ghost = nullptr;
    }

    for(auto sprite : timer) {
        if(sprite != nullptr)
            delete sprite;
        sprite = nullptr;
    }

    std::cout << "[*] Game instance destroyed!" << std::endl;
}

Game& Game::getInstance() {
    static Game instance;
    return instance;
}

void Game::processNum(int num, sf::Sprite* sprite) {
    sprite->setTextureRect(sf::IntRect((num % 5) * sprite_size, num / 5 * sprite_size, sprite_size, sprite_size));
}

void Game::stateMachine() {
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
                current_state = GameState::GAME_OVER;
                break;
            case GameState::GAME_OVER:
                this->gameOver();
                current_state = GameState::CLOSE;
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
        throw CustomException("[!] #loadTextures()# -> Buttons image not found!");
    if(!game_over_texture.loadFromFile("assets/Game_Over.png"))
        throw CustomException("[!] #loadTextures()# -> Game Over image not found!");
    if(!numbers_texture.loadFromFile("assets/Numbers.png"))
        throw CustomException("[!] #loadTextures()# -> Numbers image not found!");
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

    timer.push_back(new sf::Sprite(numbers_texture));
    timer.push_back(new sf::Sprite(numbers_texture));
    timer.push_back(new sf::Sprite(numbers_texture));

    for(int i = 0; i < timer.size(); i++) {
        timer[i]->setScale(sprite_scale, sprite_scale);
        timer[i]->setPosition(i * rect_size, rect_size);
    }

    Player player(nodes[0], player_texture, player_speed);
    player.setScale(sprite_scale, sprite_scale);
    player.setTextureOffset(0, 3);

    ghosts.push_back(new Ghost(nodes[22], ghost_texture, ghost_speed, GhostName::PYTHON));
    ghosts.push_back(new Ghost(nodes[23], ghost_texture, ghost_speed, GhostName::C));
    ghosts.push_back(new Ghost(nodes[24], ghost_texture, ghost_speed, GhostName::VHDL));
    for(int i = 0; i < ghosts.size(); i++) {
        ghosts[i]->setScale(sprite_scale, sprite_scale);
        ghosts[i]->setTextureOffset(2 * i, 4);
    }

    float delta_time = 0.0f;
    float player_timer = 0.0f;

    while(this->isOpen()) {
        if(this->handleEvent())
            break;

        delta_time = clock.restart().asSeconds();
        player_timer += delta_time;

        player.update(delta_time);
        for(auto ghost : ghosts)
            ghost->update(delta_time);

        int seconds = static_cast<int>(player_timer);
        for(int i = timer.size() - 1; i >=0; i--) {
            processNum(seconds % 10, timer[i]);
            seconds /= 10;
        }

        this->clear();

        this->draw(background);

        for(auto sprite : timer)
            this->draw(*sprite);

        // this->drawNodes();

        this->draw(player);

        for(auto ghost : ghosts)
            this->draw(*ghost);

        this->display();

        if(player.collideGhosts(ghosts))
            break;

    }

    std::cout << "Player timer: " << player_timer << std::endl;
}

void Game::gameOver() {
    sf::Sprite background(game_over_texture);
    background.setScale(sprite_scale, sprite_scale);

    while(this->isOpen()) {
        if(this->handleEvent())
            break;

        this->clear();
        this->draw(background);
        this->display();
    }
}
