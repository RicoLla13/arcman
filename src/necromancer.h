#ifndef NECROMANCER_CLASS
#define NECROMANCER_CLASS

#include <string>
#include "hero.h"
#include "wizard.h"

namespace RPG {
    class Necromancer : public Wizard {
        protected:
            int mana;
        public:
            Necromancer();
            Necromancer(int, int, int, double, std::string, int);
            ~Necromancer();
            void interact(const Hero&) override;
            void riseUndeads();
    };
}

#endif
