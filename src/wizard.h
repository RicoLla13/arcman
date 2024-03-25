#ifndef WIZARD_CLASS
#define WIZARD_CLASS

#include <string>
#include "hero.h"

namespace RPG {
    class Wizard : public Hero {
        protected:
            int mana;

        public:
            Wizard();
            Wizard(int, int, int, double, std::string, int);
            ~Wizard();
            void show() const override;
            void interact(const Hero&) override;
            void castSpell();

            // getters
            int getMana() const;
            //setters
            void setMana(int);
    };
}

#endif
