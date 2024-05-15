#include "global.hpp"

bool isOppositeDirection(const Direction& d1, const Direction& d2) {
    return (d1 == Direction::UP && d2 == Direction::DOWN) ||
           (d1 == Direction::DOWN && d2 == Direction::UP) ||
           (d1 == Direction::LEFT && d2 == Direction::RIGHT) ||
           (d1 == Direction::RIGHT && d2 == Direction::LEFT);
}
