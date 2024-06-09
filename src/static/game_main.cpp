#include "game.hpp"

Game::Game() {
    this->create(sf::VideoMode(window_width, window_height), window_title);
    this->setFramerateLimit(frame_rate);
    this->setKeyRepeatEnabled(false);
    srand(static_cast<unsigned int>(time(0)));
}

Game::~Game() {
    this->close();

    if(player != nullptr)
        delete player;
    
    player = nullptr;

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

    for(auto sprite : progress) {
        if(sprite != nullptr)
            delete sprite;
        sprite = nullptr;
    }

    for(auto& row : pellets) {
        for(auto pellet : row) {
            if(pellet != nullptr)
                delete pellet;
            pellet = nullptr;
        }
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

void Game::checkPellets() {
    sf::Vector2f player_pos = player->getPosition();

    std::vector<StaticEntity*> around;

    around.push_back(pellets[static_cast<int>(ceil(player_pos.y / rect_size))][static_cast<int>(ceil(player_pos.x / rect_size))]);
    around.push_back(pellets[static_cast<int>(ceil(player_pos.y / rect_size) + 1)][static_cast<int>(ceil(player_pos.x / rect_size))]);
    around.push_back(pellets[static_cast<int>(ceil(player_pos.y / rect_size))][static_cast<int>(ceil(player_pos.x / rect_size) + 1)]);
    around.push_back(pellets[static_cast<int>(ceil(player_pos.y / rect_size) + 1)][static_cast<int>(floor(player_pos.x / rect_size) + 1)]);

    for(auto pellet : around) {
        if(player->collide(pellet)) {
            pellet->is_eaten = true;

            if(BigPellet* big_pellet = dynamic_cast<BigPellet*>(pellet))
                player_timer -= big_pellet_bonus;

            pellet_num--;
        }
    }
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
                this->initNodes();
                this->initPellets();
                current_state = GameState::MENU;
                break;
            case GameState::MENU:
                current_state = this->menu();
                break;
            case GameState::RUN:
                current_state = this->loop();
                break;
            case GameState::GAME_WON:
                current_state = this->gameWon();;
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
    if(!pellet_texture.loadFromFile("assets/Pellet.png"))
        throw CustomException("[!] #loadTextures()# -> Pellet image not found!");
    if(!game_won_texture.loadFromFile("assets/Game_Won.png"))
        throw CustomException("[!] #loadTextures()# -> Game Won image not found!");
}

void Game::initPellets() {
    std::array<std::string, tile_grid_height> level = {
        "123456789ABCDEF",
        "2--------------",
        "3--------------",
        "4******-******-",
        "5*----*-*----*-",
        "6*----*#*----*-",
        "7******-******-",
        "8---*-----*----",
        "9---***#***----",
        "0---*-----*----",
        "1---*-----*----",
        "2---*-----*----",
        "3******-******-",
        "4*--*-*#*-*--*-",
        "5*--*-*-*-*--*-",
        "6******-******-",
        "7--------------",
        "8--------------"
    };

    for(int i = 0; i < tile_grid_height; i++) {
        for(int j = 0; j < tile_grid_width; j++) {
            switch(level[i][j]) {
                case '*':
                    pellets[i][j] = new SmallPellet(sf::Vector2f(j * rect_size, i * rect_size), pellet_texture);
                    pellet_num++;
                    break;
                case '#':
                    pellets[i][j] = new BigPellet(sf::Vector2f(j * rect_size, i * rect_size), pellet_texture);
                    pellet_num++;
                    break;
                default:
                    pellets[i][j] = nullptr;
                    break;
            }
        }
    }

    init_pellet_num = pellet_num;
}

GameState Game::menu() {
    background.setTexture(menu_texture);
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

GameState Game::loop() {
    background.setTexture(maze_texture);
    background.setScale(sprite_scale, sprite_scale);

    timer.push_back(new sf::Sprite(numbers_texture));
    timer.push_back(new sf::Sprite(numbers_texture));
    timer.push_back(new sf::Sprite(numbers_texture));

    progress.push_back(new sf::Sprite(numbers_texture));
    progress.push_back(new sf::Sprite(numbers_texture));
    progress.push_back(new sf::Sprite(numbers_texture));

    for(int i = 0; i < timer.size(); i++) {
        timer[i]->setScale(sprite_scale, sprite_scale);
        timer[i]->setPosition(i * rect_size, rect_size);

        progress[i]->setScale(sprite_scale, sprite_scale);
        progress[i]->setPosition((i + 11) * rect_size, rect_size);
    }

    player = new Player(nodes[0], player_texture, player_speed);
    player->setTextureOffset(0, 3);

    ghosts.push_back(new Ghost(nodes[22], ghost_texture, ghost_speed, GhostName::PYTHON));
    ghosts.push_back(new Ghost(nodes[23], ghost_texture, ghost_speed, GhostName::C));
    ghosts.push_back(new Ghost(nodes[24], ghost_texture, ghost_speed, GhostName::VHDL));
    for(int i = 0; i < ghosts.size(); i++) {
        ghosts[i]->setScale(sprite_scale, sprite_scale);
        ghosts[i]->setTextureOffset(2 * i, 4);
    }

    float delta_time = 0.0f;
    player_timer = 0.0f;
    clock.restart();

    while(this->isOpen()) {
        if(this->handleEvent())
            return GameState::CLOSE;

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::P))
            return GameState::GAME_WON;

        delta_time = clock.restart().asSeconds();
        player_timer += delta_time;

        player->update(delta_time);
        for(auto ghost : ghosts)
            ghost->update(delta_time);

        int seconds = static_cast<int>(player_timer);
        int loc_progress = 100 - static_cast<int>(static_cast<float>(pellet_num) / static_cast<float>(init_pellet_num) * 100);
        for(int i = timer.size() - 1; i >= 0; i--) {
            processNum(seconds % 10, timer[i]);
            seconds /= 10;

            processNum(loc_progress % 10, progress[i]);
            loc_progress /= 10;
        }

        this->checkPellets();

        this->clear();

        this->draw(background);

        for(auto sprite : timer)
            this->draw(*sprite);

        for(auto sprite : progress)
            this->draw(*sprite);

        for(auto& row : pellets) {
            for(auto pellet : row)
                if(pellet != nullptr && !pellet->is_eaten)
                    this->draw(*pellet);
        }

        this->draw(*player);

        for(auto ghost : ghosts)
            this->draw(*ghost);

        this->display();

        if(player->collideGhosts(ghosts))
            return GameState::GAME_OVER;
        if(pellet_num == 0)
            return GameState::GAME_WON;
    }

    return GameState::CLOSE;
}

GameState Game::gameWon() {
    sf::Sprite background(game_won_texture);
    background.setScale(sprite_scale, sprite_scale);

    Entity button_menu(button_texture);
    button_menu.setTextureRect(sf::IntRect(0, 5 * sprite_size, 5 * sprite_size , sprite_size));
    button_menu.setPosition(5 * rect_size, 9 * rect_size);

    Entity button_top(button_texture);
    button_top.setTextureRect(sf::IntRect(0, 6 * sprite_size, 5 * sprite_size , sprite_size));
    button_top.setPosition(5 * rect_size, 11 * rect_size);

    Entity button_exit(button_texture);
    button_exit.setTextureRect(sf::IntRect(0, 2 * sprite_size, 5 * sprite_size , sprite_size));
    button_exit.setPosition(5 * rect_size, 13 * rect_size);

    while(timer.size() < 4)
        timer.push_back(new sf::Sprite(numbers_texture));

    for(int i = 0; i < timer.size(); i++) {
        timer[i]->setScale(sprite_scale, sprite_scale);
        if(i < 3)
            timer[i]->setPosition((5 + i) * rect_size, 7 * rect_size);
        else
            timer[i]->setPosition((6 + i) * rect_size, 7 * rect_size);
    }

    int seconds = static_cast<int>(player_timer*10);
    for(int i = timer.size() - 1; i >= 0; i--) {
        processNum(seconds % 10, timer[i]);
        seconds /= 10;
    }

    bool w_was_pressed = false;
    bool s_was_pressed = false;

    int selection = 0;
    while(this->isOpen()) {
        if(this->handleEvent())
            break;

        bool w_is_pressed = sf::Keyboard::isKeyPressed(sf::Keyboard::W);
        bool s_is_pressed = sf::Keyboard::isKeyPressed(sf::Keyboard::S);

        if(!w_was_pressed && w_is_pressed) {
            selection--;
            if(selection < 0)
                selection = 2;
        }
        if(!s_was_pressed && s_is_pressed) {
            selection++;
            if(selection > 2)
                selection = 0;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
            switch(selection) {
                case 0:
                    return GameState::MENU;
                default:
                    return GameState::CLOSE;
            }
        }

        w_was_pressed = w_is_pressed;
        s_was_pressed = s_is_pressed;

        switch(selection) {
            case 0:
                button_exit.setTextureRect(sf::IntRect(0, 2 * sprite_size, 5 * sprite_size , sprite_size));
                button_menu.setTextureRect(sf::IntRect(0, 5 * sprite_size, 5 * sprite_size , sprite_size));
                button_top.setTextureRect(sf::IntRect(0, 6 * sprite_size, 5 * sprite_size , sprite_size));
                break;
            case 1:
                button_exit.setTextureRect(sf::IntRect(0, 2 * sprite_size, 5 * sprite_size , sprite_size));
                button_menu.setTextureRect(sf::IntRect(0, 4 * sprite_size, 5 * sprite_size , sprite_size));
                button_top.setTextureRect(sf::IntRect(0, 7 * sprite_size, 5 * sprite_size , sprite_size));
                break;
            case 2:
                button_exit.setTextureRect(sf::IntRect(0, 3 * sprite_size, 5 * sprite_size , sprite_size));
                button_menu.setTextureRect(sf::IntRect(0, 4 * sprite_size, 5 * sprite_size , sprite_size));
                button_top.setTextureRect(sf::IntRect(0, 6 * sprite_size, 5 * sprite_size , sprite_size));
                break;
            default:
                button_top.setTextureRect(sf::IntRect(0, 2 * sprite_size, 5 * sprite_size , sprite_size));
                button_menu.setTextureRect(sf::IntRect(0, 4 * sprite_size, 5 * sprite_size , sprite_size));
                button_top.setTextureRect(sf::IntRect(0, 6 * sprite_size, 5 * sprite_size , sprite_size));
                break;
        }

        this->clear();
        this->draw(background);

        this->draw(button_menu);
        this->draw(button_top);
        this->draw(button_exit);

        for(auto sprite : timer)
            this->draw(*sprite);

        this->display();
    }

    return GameState::CLOSE;
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
