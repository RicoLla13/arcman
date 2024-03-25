#include "sword.h"

namespace RPG {
    Sword::Sword(int damage) : damage(damage) {}
    int Sword::getDamage() const {
        return this->damage;
    }
}
