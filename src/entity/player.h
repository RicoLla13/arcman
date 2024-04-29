#ifndef PLAYER_CLASS
#define PLAYER_CLASS

#include "moving_entity.h"

class Player : public MovingEntity {
    private:
        int score;
        int anim_offset = 0;
        int dir_offset = 0;
        float elapsed_time = 0;
        const float anim_interval = 0.1f;
    public:
        Player(const sf::Vector2f& grid_position, float velocity, const sf::Texture& texture);
        ~Player() {}
        void increaseScore(int value);
        void update(float delta_time);
        int getScore() const { return score; }
};

#endif
