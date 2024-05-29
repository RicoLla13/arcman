#include "static/game.hpp"

#include <iostream>

/*
 * ARCMAN -> C++ Object-Oriented Programming project
 *
 * ### Liviu-Andrei Arsenescu, first year ISC, IL ###
 *
 * Project made during the OOP C++ course at 
 * HE-ARC Neuchâtel, Switzerland
 */

/*
 * The main function will be used as a manager
 * for the "state machine" of the game instance
 */

int main() {
    Game& game = Game::getInstance();

    game.setupTestNodes();

    try {
        game.loadTextures();
    } catch(CustomException& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    game.gameLoop();

    return 0;
}
