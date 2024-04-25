#ifndef PLAYER_CLASS
#define PLAYER_CLASS

#include "moving_entity.h"

class Player : public MovingEntity {
    private:
        int score;
    public:
        Player(const sf::Vector2f& grid_position, float velocity, const sf::Texture& texture, int size);
        ~Player() {}
        void increaseScore(int value);
        int getScore() const { return score; }
};

#endif
