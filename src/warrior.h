#ifndef WARRIOR_CLASS
#define WARRIOR_CLASS

#include "hero.h"
#include <string>

namespace RPG {
    class Warrior : public Hero {
        public:
            Warrior();
            Warrior(int, int, int, double, std::string);
            ~Warrior();
            void interact(const Hero&) override;
    };
}

#endif
