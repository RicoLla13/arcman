#include <iostream>
#include "hero.h"
#include "sword.h"

int main(void) {
    Sword *ptrSword1 = new Sword(123);
    Sword *ptrSword2 = new Sword(456);
    He_Arc::RPG::Hero hero1(10, 5, 1, 20, "Gimli", ptrSword1);
    He_Arc::RPG::Hero hero2(11, 6, 2, 21, "Gandalf", ptrSword2);

    hero1.show();
    hero2.show();

    std::cout << hero1 << hero2;

    hero1.interact(hero2);

    return 0;
}
