#ifndef HERO_CLASS
#define HERO_CLASS

#include <string>
#include "sword.h"

namespace RPG {
    class Hero {
        protected:
            int strength = 0;
            int agility = 0;
            int intelligence = 0;
            double hp = 0.0;
            std::string name = "";

        public:
            Hero();
            Hero(int, int, int, double, std::string);
            virtual ~Hero();
            virtual void show() const;
            virtual void interact(const Hero&);

            // getters
            int getStrength() const;
            int getAgility() const;
            int getIntelligence() const;
            double getHp() const;
            std::string getName() const;
            // setters
            void setStrength(int);
            void setAgility(int);
            void setIntelligence(int);
            void setHp(double);
            void setName(std::string);
    };
}

#endif
