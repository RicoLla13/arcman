#ifndef TILE_CLASS
#define TILE_CLASS

#include "entity.h"

class Tile : public Entity {
    private:
        bool isSolid;
            
    public:
        Tile(const sf::Vector2f& grid_position, const sf::Texture& texture, int size, bool isSolid);
        bool isTileSolid() const { return isSolid; }
        ~Tile() {}
};

#endif
