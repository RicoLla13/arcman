#include "hero.h"
#include <iostream>

namespace RPG {
    Hero::Hero(
            int _strength,
            int _agility,
            int _intelligence,
            double _hp,
            std::string _name) : 
        strength(_strength),
        agility(_agility),
        intelligence(_intelligence),
        hp(_hp),
        name(_name) {}

    Hero::~Hero() {}

    void Hero::show() const {
        std::cout << "============" << std::endl
            << "HERO: " << this->name << std::endl
            << "============" << std::endl
            << "strength: " << this->strength << std::endl
            << "agility: " << this-> agility << std::endl
            << "intelligence: " << this->intelligence << std::endl
            << "HP: " << this->hp << std::endl;
    }

    // getters
    int Hero::getStrength() const { return this->strength; }

    int Hero::getAgility() const { return this->agility; }

    int Hero::getIntelligence() const { return this->intelligence; }

    double Hero::getHp() const { return this->hp; }

    std::string Hero::getName() const { return this->name; }

    IObject* Hero::getObject() const { return this->pObject; }

    // setters
    void Hero::setStrength(int _strength) {
        this->strength = _strength;
    }

    void Hero::setAgility(int _agility) {
        this->agility = _agility;
    }

    void Hero::setIntelligence(int _intelligence) {
        this->intelligence = _intelligence;
    }

    void Hero::setHp(double _hp) {
        this->hp = _hp;
    }

    void Hero::setName(std::string _name) {
        this->name = _name;
    }

    void Hero::setObject(IObject* _pObject) {
        this->pObject = _pObject;
    }
}
