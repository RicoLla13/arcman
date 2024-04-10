#ifndef SHIELD_CLASS
#define SHIELD_CLASS

#include "i_object.h"

namespace RPG {
    class Shield : public IObject {
        private:
            int solidity;
        public:
            Shield(int);
            int getDefense() const;
            void getName() const override;
            void getFeature() const override;
    };
}

#endif
