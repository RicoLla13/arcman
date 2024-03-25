#ifndef SWORD_CLASS
#define SWORD_CLASS

namespace RPG {
    class Sword {
        private:
            int damage;

        public:
            Sword(int);
            int getDamage() const;
    };
}

#endif
