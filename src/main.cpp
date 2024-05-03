#include "static/game.h"

int main() {
    Game& game = Game::getInstance();

    std::array<std::string, tile_grid_height> map = {
        "###############",
        "#             #",
        "# ### ### ### #",
        "# # # # # # # #",
        "# # # # # # # #",
        "# # # # # # # #",
        "# # # # # # # #",
        "# # # # # # # #",
        "# # # # # # # #",
        "# # # # # # # #",
        "# # # # # # # #",
        "# # # # # # # #",
        "# # # # # # # #",
        "# # # # # # # #",
        "# # # # # # # #",
        "# ### ### ### #",
        "#             #",
        "###############"
    };

    game.loadTextures();
    game.convertMap(map);
    game.gameLoop();

    return 0;
}
