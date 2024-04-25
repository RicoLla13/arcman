#ifndef TILE_CLASS
#define TILE_CLASS

#include "entity.h"

class Tile : public Entity {
    private:
        bool isSolid;
            
    public:
        Tile(const sf::Vector2f& position, const sf::Vector2f& grid_position, sf::Texture& texture, bool isSolid);
        ~Tile() {}
};

#endif
