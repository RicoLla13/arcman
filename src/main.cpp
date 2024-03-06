#include <iostream>
#include "hero.h"

int main(void) {
    He_Arc::RPG::Hero hero1(10, 5, 1, 20, "Gimli");
    He_Arc::RPG::Hero hero2(11, 6, 2, 21, "Gandalf");

    hero1.show();
    hero2.show();

    hero1.interact(hero2);

    return 0;
}
