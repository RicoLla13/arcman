#include <iostream>
#include "sword.h"

namespace RPG {
    Sword::Sword(int damage) : damage(damage) {}

    int Sword::getDamage() const {
        return this->damage;
    }

    void Sword::getName() const {
        std::cout << "Sword" << std::endl;
    }

    void Sword::getFeature() const {
        std::cout << "Damage: " << this->damage << std::endl;
    }
}
