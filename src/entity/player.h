#ifndef PLAYER_CLASS
#define PLAYER_CLASS

#include "moving_entity.h"

class Player : public MovingEntity {
    private:
        int score;
    public:
        Player(const sf::Vector2f& position, const sf::Vector2f& grid_position, float velocity, sf::Texture& texture);
        ~Player() {}
        void increaseScore(int value);
        int getScore() const { return score; }
};

#endif
