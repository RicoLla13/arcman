#include "wizard.h"
#include "hero.h"
#include <iostream>
#include <string>

namespace RPG {
    Wizard::Wizard() : Hero(), mana(0) {}
    Wizard::Wizard(
            int _strength,
            int _agility,
            int _intelligence,
            double _hp,
            std::string _name,
            int _mana) : 
        Hero(_strength, _agility, _intelligence, _hp, _name),
        mana(0) {}
    Wizard::~Wizard() {}
    void Wizard::interact(const Hero& otherHero) {
        std::cout << "?: What is your name, brave hero?" 
            << std::endl
            << "I: I am " << this->name << ". " 
            << "I am a wizard. " << std::endl
            << "To whom do I have the pleasure?" << std::endl
            << otherHero.getName() << ": People call me " 
            << otherHero.getName() << std::endl;
    }
    void Wizard::show() const {
        Hero::show();
        std::cout << "Mana: " << this->mana << std::endl;
    }
    void Wizard::castSpell() {
        std::cout << this->name << ": "
            << "I cast a spell!" << std::endl;
    }

    // getters
    int Wizard::getMana() const { return this->mana; }
    // setters
    void Wizard::setMana(int _mana) { this->mana = _mana; }
}
