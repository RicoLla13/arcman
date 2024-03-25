#include <iostream>
#include <list>
#include <algorithm>
#include "hero.h"
#include "wizard.h"
#include "warrior.h"
#include "necromancer.h"
#include "sword.h"

int main(void) {
    std::list<RPG::Hero*> heroes;

    RPG::Warrior* warrior1 = new RPG::Warrior(10, 10, 10, 1.2, "Warrior 1");
    RPG::Warrior* warrior2 = new RPG::Warrior(10, 10, 10, 1.2, "Warrior 2");
    RPG::Wizard* wizard1 = new RPG::Wizard(20, 20, 20, 1.2, "Wizard1", 10);
    RPG::Wizard* wizard2 = new RPG::Wizard(20, 20, 20, 1.2, "Wizard2", 10);
    RPG::Necromancer* necromancer = new RPG::Necromancer(30, 30, 30, 1.2, "Necromancer", 20);

    heroes.push_back(warrior1);
    heroes.push_back(warrior2);
    heroes.push_back(wizard1);
    heroes.push_back(wizard2);
    heroes.push_back(necromancer);

    std::for_each(heroes.begin(), heroes.end(), [](RPG::Hero* hero) {
        hero->show();
    });
    return 0;
}
