#ifndef Archer_H
#define Archer_H

#include "Unit.h"

class Archer : public Unit {
    private:

    public:
    Archer(Vector3 position);
    ~Archer();

    // FIXME think about this.
    static const char* getModelFileName() {
        return "assets/box.fbx";
    }

};

#endif