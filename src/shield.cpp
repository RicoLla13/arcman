#include <iostream>
#include "shield.h"

namespace RPG {
    Shield::Shield(int solidity) : solidity(solidity) {}
    int Shield::getDefense() const {
        return this->solidity;
    }
    void Shield::getName() const {
        std::cout << "Shield" << std::endl;
    }
    void Shield::getFeature() const {
        std::cout << "Solidity: " << this->solidity << std::endl;
    }
}
