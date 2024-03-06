#include "sword.h"

Sword::Sword(int damage) : damage(damage) {}

int Sword::getDagame() const {
    return this->damage;
}
