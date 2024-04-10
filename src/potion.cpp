#include <iostream>
#include "potion.h"

namespace RPG {
    Potion::Potion(int power) : power(power) {}
    int Potion::getPower() const {
        return this->power;
    }
    void Potion::getName() const {
        std::cout << "Potion" << std::endl;
    }
    void Potion::getFeature() const {
        std::cout << "Power: " << this->power << std::endl;
    }
}
