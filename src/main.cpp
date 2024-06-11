#include "static/game.hpp"
#include "logger/logger.hpp"

#include <iostream>

int main() {
    Logger* logger = Logger::getInstance();
    logger->log("Start application");

    Game* game = Game::getInstance();
    game->stateMachine();

    if(game != nullptr)
        delete game;
    game = nullptr;

    if(logger != nullptr) {
        logger->log("End application");
        delete logger;
    }
    logger = nullptr;

    return 0;
}
