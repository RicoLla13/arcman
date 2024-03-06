#include "hero.h"
#include <iostream>

namespace He_Arc::RPG {
    void Hero::interact(const Hero& otherHero) {
        std::cout << "?: What is your name, brave hero?" << std::endl
            << "I: I am " << this->name << ". "
            << "To whom do I have the pleasure?" << std::endl
            << otherHero.name << ": People call me " << otherHero.name << std::endl << std::endl;
    }

    void Hero::show() const {
        std::cout << "============" << std::endl
            << "HERO: " << this->name << std::endl
            << "============" << std::endl
            << "strength: " << this->strength << std::endl
            << "agility: " << this-> agility << std::endl
            << "intelligence: " << this->intelligence << std::endl
            << "HP: " << this->hp << std::endl << std::endl;
    }

    Hero::Hero() : strength(0), agility(0), intelligence(0), hp(0), name("") {}

    Hero::Hero(int _strength, int _agility, int _intelligence, double _hp, std::string _name) : strength(_strength), agility(_agility), intelligence(_intelligence), hp(_hp), name(_name) {}
}
