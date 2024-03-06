#ifndef HERO_CLASS
#define HERO_CLASS

#include <string>

namespace He_Arc::RPG {
    class Hero {
        public:
            Hero();
            Hero(int, int, int, double, std::string);
            void show() const;
            void interact(const Hero&);
            int getAgility() const;

        private:
            int strength;
            int agility;
            int intelligence;
            double hp;
            std::string name;
    };
}


#endif
