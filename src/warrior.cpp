#include "warrior.h"
#include "hero.h"
#include <iostream>
#include <string>

namespace RPG {
    Warrior::Warrior() : Hero() {}
    Warrior::Warrior(
            int _strength,
            int _agility,
            int _intelligence,
            double _hp,
            std::string _name) : 
        Hero(_strength, _agility, _intelligence, _hp, _name) {}
    Warrior::~Warrior() {}
    void Warrior::interact(const Hero& otherHero) {
        std::cout << "?: What is your name, brave hero?"
            << std::endl
            << "I: I am " << name << "." << std::endl
            << "I am a warrior. " << std::endl
            << "To whom do I have the pleasure?" << std::endl
            << otherHero.getName() << ": People call me "
            << otherHero.getName() << std::endl;
    }
}
