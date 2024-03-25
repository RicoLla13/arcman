#include "necromancer.h"
#include "hero.h"
#include <iostream>
#include <string>

namespace RPG {
    Necromancer::Necromancer() : Wizard() {}
    Necromancer::Necromancer(
            int _strength,
            int _agility,
            int _intelligence,
            double _hp,
            std::string _name,
            int _mana) : 
        Wizard(_strength, _agility, _intelligence, _hp, _name, _mana){}
    Necromancer::~Necromancer() {}
    void Necromancer::interact(const Hero& otherHero) {
        std::cout << "?: What is your name, brave hero?" 
            << std::endl
            << "I: I am " << this->name << ". " 
            << "I am a necromancer. " << std::endl
            << "To whom do I have the pleasure?" << std::endl
            << otherHero.getName() << ": People call me " 
            << otherHero.getName() << std::endl;
    }
    void Necromancer::riseUndeads() {
        std::cout << this->name << ": "
            << "I rise undeads!" << std::endl;
    }
}
