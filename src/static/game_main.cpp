#include "game.hpp"

// Initialize the game instance to null
Game* Game::instance = nullptr;

// Constructor
Game::Game() {
    this->create(sf::VideoMode(window_width, window_height), window_title); // Create the window
    this->setFramerateLimit(frame_rate); //  Set the frame rate limit
    srand(static_cast<unsigned int>(time(0))); // Seed the random number generator
    this->logger = Logger::getInstance(); // Get the logger instance
}

// Destructor
Game::~Game() {
    this->close(); // Close the window
}

// Singleton -> Get the current instance of the game
Game* Game::getInstance() {
    if(instance == nullptr)
        instance = new Game();

    return instance;
}

// Process a number into a sprite
void Game::processNum(int num, sf::Sprite* sprite) {
    // If the sprite does not exist, return
    if(sprite == nullptr)
        return;

    // Set the texture rectangle based on the number
    sprite->setTextureRect(sf::IntRect((num % 5) * sprite_size, num / 5 * sprite_size, sprite_size, sprite_size));
}

// Check collision between the player and surrounding pellets
void Game::checkPellets(Player* player, int& pellet_num, std::array<std::array<StaticEntity*, tile_grid_width>, tile_grid_height>& pellets) {
    // Fetch the player's position
    sf::Vector2f player_pos = player->getPosition();

    // Make a vector with the 4 surrounding pellets
    std::vector<StaticEntity*> around;

    // Calculate the grid position of the player
    int grid_x = static_cast<int>(ceil(player_pos.x / rect_size));
    int grid_y = static_cast<int>(ceil(player_pos.y / rect_size));

    // Add the surrounding pellets to the vector
    around.push_back(pellets[grid_y][grid_x]);
    around.push_back(pellets[grid_y][grid_x + 1]);
    around.push_back(pellets[grid_y + 1][grid_x]);
    around.push_back(pellets[grid_y + 1][grid_x + 1]);

    // For each pellet in the vector, check if it is collided with the player
    for(auto pellet : around) {
        if(player->collide(pellet)) {
            pellet->is_eaten = true;

            // If the pellet is a big pellet, add a bonus to the player
            if(BigPellet* big_pellet = dynamic_cast<BigPellet*>(pellet))
                player_timer -= big_pellet_bonus;

            // Decrease the pellet number
            pellet_num--;
        }
    }
}

// Game state machine
void Game::stateMachine() {
    bool stop = false; // Stop flag
    GameState current_state = GameState::INIT;

    while(!stop) {
        switch(current_state) {
            case GameState::INIT:
                try {
                    this->loadTextures();
                    current_state = GameState::MENU;
                    this->logger->log("Game initialized");
                } catch(CustomException& e) {
                    std::cerr << e.what() << std::endl;
                    this->logger->log("Encountered error while initializing game");
                    current_state = GameState::CLOSE;
                }
                break;
            case GameState::MENU:
                this->logger->log("Entered menu");
                current_state = this->menu();
                break;
            case GameState::RUN:
                this->logger->log("Started a round");
                current_state = this->loop();
                break;
            case GameState::GAME_WON:
                this->logger->log("Game won with time: " + std::to_string(player_timer) + " seconds");
                current_state = this->gameWon();
                break;
            case GameState::GAME_OVER:
                this->logger->log("Game lost");
                current_state = this->gameOver();
                break;
            default:
                stop = true;
                break;
        }
    }
}

// Handle close event of SFML window
bool Game::handleEvent() {
    sf::Event event;
    while(this->pollEvent(event)) {
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

void Game::initPellets(std::array<std::array<StaticEntity*, tile_grid_width>, tile_grid_height>& pellets) {
    // Text representation of the level
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

    // Loop to initialize pellets with the given rules
    // * -> small pellet
    // # -> big pellet
    for(int i = 0; i < tile_grid_height; i++) {
        for(int j = 0; j < tile_grid_width; j++) {
            switch(level[i][j]) {
                case '*':
                    pellets[i][j] = new SmallPellet(
                            sf::Vector2f(j * rect_size, i * rect_size), 
                            pellet_texture);
                    break;
                case '#':
                    pellets[i][j] = new BigPellet(
                            sf::Vector2f(j * rect_size, i * rect_size),
                            pellet_texture);
                    break;
                default:
                    pellets[i][j] = nullptr;
                    break;
            }
        }
    }
}

GameState Game::menu() {
    Entity background(menu_texture);

    Entity button_play(button_texture);
    button_play.setTextureRect(sf::IntRect(0, sprite_size, 5 * sprite_size , sprite_size));
    button_play.setPosition(5 * rect_size, 8 * rect_size);

    Entity button_exit(button_texture);
    button_exit.setTextureRect(sf::IntRect(0, 2 * sprite_size, 5 * sprite_size , sprite_size));
    button_exit.setPosition(5 * rect_size, 10 * rect_size);

    ret_was_pressed = true;

    int selection = 0;
    while(this->isOpen()) {
        if(this->handleEvent())

            break;

        bool w_is_pressed = sf::Keyboard::isKeyPressed(sf::Keyboard::W);
        bool s_is_pressed = sf::Keyboard::isKeyPressed(sf::Keyboard::S);
        bool ret_is_pressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Return);

        // If W is pressed go up with the button selector, or wrap
        if(!w_was_pressed && w_is_pressed) {
            selection--;
            if(selection < 0)
                selection = 1;
        }
        // If S is pressed go down with the button selector, or wrap
        if(!s_was_pressed && s_is_pressed) {
            selection++;
            if(selection > 1)
                selection = 0;
        }
        // If Return is pressed, select the button
        if(!ret_was_pressed && ret_is_pressed) {
            switch(selection) {
                case 0:
                    return GameState::RUN;
                default:
                    return GameState::CLOSE;
            }
        }

        w_was_pressed = w_is_pressed;
        s_was_pressed = s_is_pressed;
        ret_was_pressed = ret_is_pressed;

        // Update button graphics
        switch(selection) {
            case 0:
                button_play.setTextureRect(sf::IntRect(0, sprite_size, 5 * sprite_size , sprite_size));
                button_exit.setTextureRect(sf::IntRect(0, 2 * sprite_size, 5 * sprite_size , sprite_size));
                break;
            case 1:
                button_play.setTextureRect(sf::IntRect(0, 0, 5 * sprite_size , sprite_size));
                button_exit.setTextureRect(sf::IntRect(0, 3 * sprite_size, 5 * sprite_size , sprite_size));
                break;
            default:
                button_play.setTextureRect(sf::IntRect(0, 0, 5 * sprite_size , sprite_size));
                button_exit.setTextureRect(sf::IntRect(0, 2 * sprite_size, 5 * sprite_size , sprite_size));
                break;
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
    GameState result = GameState::CLOSE;

    Entity background(maze_texture);

    std::vector<Node*> nodes;
    std::array<std::array<StaticEntity*, tile_grid_width>, tile_grid_height> pellets;

    this->initNodes(nodes);
    this->initPellets(pellets);

    std::vector<Entity*> timer;
    std::vector<Entity*> progress;

    for(int i = 0; i < 3; i++) {
        timer.push_back(new Entity(numbers_texture));
        timer[i]->setPosition(i * rect_size, rect_size);

        progress.push_back(new Entity(numbers_texture));
        progress[i]->setPosition((i + 11) * rect_size, rect_size);
    }

    Player* player = new Player(nodes[0], player_texture, player_speed);
    player->setTextureOffset(0, 3);

    std::vector<Ghost*> ghosts;
    for(int i = 0; i < 3; i++) {
        ghosts.push_back(new Ghost(nodes[22 + i], ghost_texture, ghost_speed, static_cast<GhostName>(i)));
        ghosts[i]->setTextureOffset(2 * i, 4);
    }

    int init_pellet_num = 0;
    for(const auto& row : pellets) {
        for(const auto& sprite : row) {
            if(sprite != nullptr)
                init_pellet_num++;
        }
    }
    int pellet_num = init_pellet_num;

    float delta_time = 0.0f;
    player_timer = 0.0f;
    clock.restart();

    while(this->isOpen()) {
        if(this->handleEvent()) {
            result = GameState::CLOSE;
            break;
        }

        // Backdoor
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::P)) {
            result = GameState::GAME_WON;
            player_timer = 999.9f;
            break;
        }

        // Compute delta time and update player timer with it
        delta_time = clock.restart().asSeconds();
        player_timer += delta_time;

        // Update entities with delta time
        player->update(delta_time);
        for(auto& ghost : ghosts)
            ghost->update(delta_time);

        // Compute seconds and progress and update label textures
        int seconds = static_cast<int>(player_timer);
        int seconds_copy = seconds;
        int loc_progress = 100 - static_cast<int>(
                static_cast<float>(pellet_num) / 
                static_cast<float>(init_pellet_num) * 100);
        int loc_progress_copy = loc_progress;

        for(int i = timer.size() - 1; i >= 0; i--) {
            processNum(seconds_copy % 10, timer[i]);
            seconds_copy /= 10;

            processNum(loc_progress_copy % 10, progress[i]);
            loc_progress_copy /= 10;
        }

        if(seconds < 100)
            timer[0]->setTextureRect(sf::IntRect(0, 0, 0, 0));
        if(seconds < 10)
            timer[1]->setTextureRect(sf::IntRect(0, 0, 0, 0));
        if(loc_progress < 100)
            progress[0]->setTextureRect(sf::IntRect(0, 0, 0, 0));
        if(loc_progress < 10)
            progress[1]->setTextureRect(sf::IntRect(0, 0, 0, 0));

        // Pellet collision
        this->checkPellets(player, pellet_num, pellets);

        this->clear();

        this->draw(background);

        for(const auto& sprite : timer)
            this->draw(*sprite);

        for(const auto& sprite : progress)
            this->draw(*sprite);

        for(const auto& row : pellets) {
            for(const auto& pellet : row)
                if(pellet != nullptr && !pellet->is_eaten)
                    this->draw(*pellet);
        }

        this->draw(*player);

        for(const auto& ghost : ghosts)
            this->draw(*ghost);
        this->display();

        // Ghost collision -> game loosing condition
        if(player->collideGhosts(ghosts)) {
            result = GameState::GAME_OVER;
            break;
        }
        // Check if the player won
        if(pellet_num == 0) {
            result = GameState::GAME_WON;
            break;
        }
    }

    // Clean the memory
    for(auto& sprite : timer) {
        if(sprite != nullptr)
            delete sprite;
        sprite = nullptr;
    }
    timer.clear();

    for(auto& sprite : progress) {
        if(sprite != nullptr)
            delete sprite;
        sprite = nullptr;
    }
    progress.clear();

    if(player != nullptr)
        delete player;
    player = nullptr;

    for(auto& ghost : ghosts) {
        if(ghost != nullptr)
            delete ghost;
        ghost = nullptr;
    }
    ghosts.clear();

    for(auto& row : pellets) {
        for(auto& pellet : row) {
            if(pellet != nullptr)
                delete pellet;
            pellet = nullptr;
        }
    }

    for(auto& node : nodes) {
        if(node != nullptr)
            delete node;
        node = nullptr;
    }

    return result;
}

GameState Game::gameWon() {
    GameState result = GameState::CLOSE;

    Entity background(game_won_texture);

    Entity button_menu(button_texture);
    button_menu.setTextureRect(sf::IntRect(0, 5 * sprite_size, 5 * sprite_size , sprite_size));
    button_menu.setPosition(5 * rect_size, 9 * rect_size);

    Entity button_exit(button_texture);
    button_exit.setTextureRect(sf::IntRect(0, 2 * sprite_size, 5 * sprite_size , sprite_size));
    button_exit.setPosition(5 * rect_size, 11 * rect_size);

    std::vector<Entity*> timer;
    for(int i = 0; i < 4; i++) {
        timer.push_back(new Entity(numbers_texture));

        if(i < 3)
            timer[i]->setPosition((7 + i) * rect_size, 7 * rect_size);
        else
            timer[i]->setPosition((8 + i) * rect_size, 7 * rect_size);
    }

    int seconds = static_cast<int>(player_timer*10);
    int seconds_copy = seconds;   

    for(int i = timer.size() - 1; i >= 0; i--) {
        processNum(seconds_copy % 10, timer[i]);
        seconds_copy /= 10;
    }

    if(seconds < 1000)
        timer[0]->setTextureRect(sf::IntRect(0, 0, 0, 0));
    if(seconds < 100)
        timer[1]->setTextureRect(sf::IntRect(0, 0, 0, 0));

    int selection = 0;
    bool stop = false;
    while(this->isOpen() && !stop) {
        if(this->handleEvent())
            break;

        bool w_is_pressed = sf::Keyboard::isKeyPressed(sf::Keyboard::W);
        bool s_is_pressed = sf::Keyboard::isKeyPressed(sf::Keyboard::S);
        bool ret_is_pressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Return);

        if(!w_was_pressed && w_is_pressed) {
            selection--;
            if(selection < 0)
                selection = 1;
        }
        if(!s_was_pressed && s_is_pressed) {
            selection++;
            if(selection > 1)
                selection = 0;
        }
        if(!ret_was_pressed && ret_is_pressed) {
            switch(selection) {
                case 0:
                    result = GameState::MENU;
                    stop = true;
                    break;
                default:
                    stop = true;
                    break;
            }
        }

        w_was_pressed = w_is_pressed;
        s_was_pressed = s_is_pressed;
        ret_was_pressed = ret_is_pressed;

        switch(selection) {
            case 0:
                button_menu.setTextureRect(sf::IntRect(0, 5 * sprite_size, 5 * sprite_size , sprite_size));
                button_exit.setTextureRect(sf::IntRect(0, 2 * sprite_size, 5 * sprite_size , sprite_size));
                break;
            case 1:
                button_menu.setTextureRect(sf::IntRect(0, 4 * sprite_size, 5 * sprite_size , sprite_size));
                button_exit.setTextureRect(sf::IntRect(0, 3 * sprite_size, 5 * sprite_size , sprite_size));
                break;
            default:
                button_menu.setTextureRect(sf::IntRect(0, 4 * sprite_size, 5 * sprite_size , sprite_size));
                button_exit.setTextureRect(sf::IntRect(0, 2 * sprite_size, 5 * sprite_size , sprite_size));
                break;
        }

        this->clear();
        this->draw(background);

        this->draw(button_menu);
        this->draw(button_exit);

        for(const auto& sprite : timer)
            this->draw(*sprite);

        this->display();
    }

    for(auto& sprite : timer) {
        if(sprite != nullptr)
            delete sprite;
        sprite = nullptr;
    }
    timer.clear();

    return result;
}

GameState Game::gameOver() {
    GameState result = GameState::CLOSE;
    Entity background(game_over_texture);

    Entity button_menu(button_texture);
    button_menu.setTextureRect(sf::IntRect(0, 5 * sprite_size, 5 * sprite_size , sprite_size));
    button_menu.setPosition(5 * rect_size, 9 * rect_size);

    Entity button_exit(button_texture);
    button_exit.setTextureRect(sf::IntRect(0, 2 * sprite_size, 5 * sprite_size , sprite_size));
    button_exit.setPosition(5 * rect_size, 11 * rect_size);

    int selection = 0;
    bool stop = false;
    while(this->isOpen() && !stop) {
        if(this->handleEvent())
            break;

        bool w_is_pressed = sf::Keyboard::isKeyPressed(sf::Keyboard::W);
        bool s_is_pressed = sf::Keyboard::isKeyPressed(sf::Keyboard::S);
        bool ret_is_pressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Return);

        if(!w_was_pressed && w_is_pressed) {
            selection--;
            if(selection < 0)
                selection = 1;
        }
        if(!s_was_pressed && s_is_pressed) {
            selection++;
            if(selection > 1)
                selection = 0;
        }
        if(!ret_was_pressed && ret_is_pressed) {
            switch(selection) {
                case 0:
                    result = GameState::MENU;
                    stop = true;
                    break;
                default:
                    stop = true;
                    break;
            }
        }

        w_was_pressed = w_is_pressed;
        s_was_pressed = s_is_pressed;
        ret_was_pressed = ret_is_pressed;

        switch(selection) {
            case 0:
                button_menu.setTextureRect(sf::IntRect(0, 5 * sprite_size, 5 * sprite_size , sprite_size));
                button_exit.setTextureRect(sf::IntRect(0, 2 * sprite_size, 5 * sprite_size , sprite_size));
                break;
            case 1:
                button_menu.setTextureRect(sf::IntRect(0, 4 * sprite_size, 5 * sprite_size , sprite_size));
                button_exit.setTextureRect(sf::IntRect(0, 3 * sprite_size, 5 * sprite_size , sprite_size));
                break;
            default:
                button_menu.setTextureRect(sf::IntRect(0, 4 * sprite_size, 5 * sprite_size , sprite_size));
                button_exit.setTextureRect(sf::IntRect(0, 2 * sprite_size, 5 * sprite_size , sprite_size));
                break;
        }

        this->clear();
        this->draw(background);

        this->draw(button_menu);
        this->draw(button_exit);

        this->display();
    }

    return result;
}
