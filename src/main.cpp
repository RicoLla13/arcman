#include "static/game.hpp"

int main() {
    Game& game = Game::getInstance();

    game.gameLoop();

    return 0;
}
