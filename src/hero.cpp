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
            << "HP: " << this->hp << std::endl
            << "Sword damage: " << this->ptrSword->getDamage() << std::endl << std::endl;
    }

    Hero::Hero() : strength(0), agility(0), intelligence(0), hp(0), name("") {}

    Hero::Hero(const Hero& other) : strength(other.strength), agility(other.agility), intelligence(other.intelligence), name(other.name) {
        ptrSword = new Sword(*other.ptrSword);
    }

    Hero::Hero(int _strength, int _agility, int _intelligence, double _hp, std::string _name, Sword *ptrSword) : strength(_strength), agility(_agility), intelligence(_intelligence), hp(_hp), name(_name), ptrSword(ptrSword){}

    Hero::~Hero() {
        if(ptrSword != nullptr) {
            delete ptrSword;
            ptrSword = nullptr;
        }
    }

    std::ostream& operator<<(std::ostream& os, const Hero& h) {
        os << "============" << std::endl
            << "HERO: " << h.name << std::endl
            << "============" << std::endl
            << "strength: " << h.strength << std::endl
            << "agility: " << h.agility << std::endl
            << "intelligence: " << h.intelligence << std::endl
            << "HP: " << h.hp << std::endl
            << "Sword damage: " << h.ptrSword->getDamage() << std::endl << std::endl;

        return os;
    }
}
