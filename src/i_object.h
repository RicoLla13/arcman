#ifndef IOBJECT_CLASS
#define IOBJECT_CLASS

namespace RPG {
    class IObject {
        public:
            IObject() = default;
            void virtual getName() const = 0;
            void virtual getFeature() const = 0;
    };
}

#endif
