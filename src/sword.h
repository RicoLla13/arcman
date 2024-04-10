#ifndef SWORD_CLASS
#define SWORD_CLASS

#include "i_object.h"

namespace RPG {
    class Sword : public IObject {
        private:
            int damage;

        public:
            Sword(int);
            int getDamage() const;
            void getName() const override;
            void getFeature() const override;
    };
}

#endif
