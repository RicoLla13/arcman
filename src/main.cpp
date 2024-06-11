#include "static/game.hpp"
#include "logger/logger.hpp"

#include <iostream>

int main() {
    Logger& logger = Logger::getInstance();
    logger << "[" << logger.getCurrentTime() << "] Start application" << std::endl;

    Game& game = Game::getInstance();
    game.stateMachine();

    return 0;
}
