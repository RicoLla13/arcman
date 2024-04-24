#ifndef STATIC_ENTITY_CLASS
#define STATIC_ENTITY_CLASS

#include "entity.h"

class StaticEntity : public Entity {
    protected:
        int score_value;

    public:
        StaticEntity(std::string texture_path, int x_pos, int y_pos, int score_value);
        virtual ~StaticEntity();
        void draw(sf::Window& window) override;
};

#endif
