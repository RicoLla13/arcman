#ifndef HERO_CLASS
#define HERO_CLASS

#include <string>
#include "i_object.h"
#include "backpack.h"

namespace RPG {
    class Hero {
        protected:
            int strength = 0;
            int agility = 0;
            int intelligence = 0;
            double hp = 0.0;
            std::string name = "";
            IObject* pObject = nullptr;

        public:
            Backpack backpack;

            Hero() = default;
            Hero(const Hero&) = delete;
            Hero(int, int, int, double, std::string);
            virtual ~Hero();
            virtual void show() const;
            virtual void interact(const Hero&) = 0;
            Hero& operator=(const Hero&) = delete;

            // getters
            int getStrength() const;
            int getAgility() const;
            int getIntelligence() const;
            double getHp() const;
            std::string getName() const;
            IObject* getObject() const;
            // setters
            void setStrength(int);
            void setAgility(int);
            void setIntelligence(int);
            void setHp(double);
            void setName(std::string);
            void setObject(IObject*);
    };
}

#endif
