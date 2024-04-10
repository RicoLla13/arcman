#include <iostream>
#include <list>
#include <algorithm>
#include "hero.h"
#include "wizard.h"
#include "warrior.h"
#include "necromancer.h"
#include "i_object.h"
#include "sword.h"
#include "shield.h"
#include "potion.h"

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

    RPG::Sword* sword1 = new RPG::Sword(10);
    RPG::Sword* sword2 = new RPG::Sword(20);
    RPG::Sword* sword3 = new RPG::Sword(30);

    RPG::Shield* shield1 = new RPG::Shield(10);
    RPG::Shield* shield2 = new RPG::Shield(20);

    RPG::Potion* potion1 = new RPG::Potion(10);
    RPG::Potion* potion2 = new RPG::Potion(20);

    warrior1->backpack.pack(sword1);
    warrior1->backpack.pack(sword2);
    warrior1->backpack.pack(sword3);
    warrior1->backpack.pack(shield1);
    warrior1->backpack.pack(shield2);
    warrior1->backpack.pack(potion1);
    warrior1->backpack.pack(potion2);

    while(warrior1->backpack.isNotEmpty()) {
        RPG::IObject* object = warrior1->backpack.unpack();
        object->getName();
        delete object;
    }
    return 0;
}
