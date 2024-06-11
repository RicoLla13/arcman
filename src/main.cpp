#include "static/game.hpp"
#include "logger/logger.hpp"

int main() {
    // Creating the logger instance
    Logger* logger = Logger::getInstance();
    logger->log("Start application");

    // Creating the game instance
    Game* game = Game::getInstance();
    game->stateMachine();

    // Final resource cleanup
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
