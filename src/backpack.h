#ifndef BACKPACK_CLASS
#define BACKPACK_CLASS

#include "i_object.h"
#include <stack>

namespace RPG {
    class Backpack {
        private:
            std::stack<IObject*> objects;
        public:
            Backpack() = default;
            virtual ~Backpack() = default;
            void pack(IObject*);
            IObject* unpack();
            bool isNotEmpty() const;
    };
}

#endif
