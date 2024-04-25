#ifndef PLAYER_CLASS
#define PLAYER_CLASS

#include "moving_entity.h"

class Player : public MovingEntity {
    private:
        int score;
    public:
        Player(int x_pos, int y_pos, float velocity, sf::Texture& texture);
        ~Player() {}
        void setDirection(int x_dir, int y_dir);
        void setTextureOffset(int x_off, int y_off, int size);
        void move();
        void increaseScore(int value);
        int getScore() const { return score; }
};

#endif
