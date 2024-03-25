#include <iostream>
#include "hero.h"
#include "wizard.h"
#include "warrior.h"
#include "necromancer.h"
#include "sword.h"

int main(void) {
    RPG::Warrior warrior(10, 10, 10, 2.3, "Warrior");
    RPG::Wizard wizard(20, 20, 20, 5.3, "Wizard", 100);
    RPG::Necromancer necromancer(20, 20, 20, 5.3, "Necromancer", 100);

    warrior.show();
    wizard.show();
    necromancer.show();

    warrior.interact(wizard);
    wizard.interact(warrior);
    necromancer.interact(warrior);

    wizard.castSpell();
    necromancer.riseUndeads();
    return 0;
}
