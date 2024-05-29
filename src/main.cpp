#include "static/game.hpp"

#include <iostream>

int main() {
    Game& game = Game::getInstance();

    game.state_machine();

    return 0;
}
