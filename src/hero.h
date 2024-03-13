#ifndef HERO_CLASS
#define HERO_CLASS

#include <string>
#include "sword.h"

namespace He_Arc::RPG {
    class Hero {
        public:
            Hero();
            Hero(int, int, int, double, std::string, Sword*);
            Hero(const Hero&);
            ~Hero();
            void show() const;
            void interact(const Hero&);
            int getAgility() const;
            friend std::ostream& operator<<(std::ostream&, const Hero&);

        private:
            int strength = 0;
            int agility = 0;
            int intelligence = 0;
            double hp = 0.0;
            std::string name = "";
            Sword* ptrSword = nullptr;
    };
}


#endif
