#ifndef POTION_CLASS
#define POTION_CLASS

#include "i_object.h"

namespace RPG {
    class Potion : public IObject {
        private:
            int power;
        public:
            Potion(int);
            int getPower() const;
            void getName() const override;
            void getFeature() const override;
    };
}

#endif
