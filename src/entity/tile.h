#ifndef TILE_CLASS
#define TILE_CLASS

#include "entity.h"

class Tile : public Entity {
    private:
        bool solid;
            
    public:
        Tile(const sf::Vector2f& grid_position, const sf::Texture& texture, bool isSolid);
        bool isSolid() const { return solid; }
        ~Tile() {}
};

#endif
