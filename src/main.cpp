#include "static/game.hpp"

#include <iostream>

int main() {
    Game& game = Game::getInstance();

    game.setupTestNodes();

    try {
        game.loadTextures();
        game.gameLoop();
    } catch(CustomException& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}
