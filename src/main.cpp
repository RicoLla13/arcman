#include "static/game.hpp"

#include <iostream>

int main() {
    Game& game = Game::getInstance();

    game.stateMachine();

    return 0;
}
