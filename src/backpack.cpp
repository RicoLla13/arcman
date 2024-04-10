#include <iostream>
#include <stack>
#include "backpack.h"

namespace RPG {
    void Backpack::pack(IObject* object) {
        this->objects.push(object);
    }
    IObject* Backpack::unpack() {
        IObject* object = this->objects.top();
        this->objects.pop();
        return object;
    }
    bool Backpack::isNotEmpty() const {
        return !this->objects.empty();
    }
}
