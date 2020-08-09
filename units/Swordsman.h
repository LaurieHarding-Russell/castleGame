#ifndef Swordsman_H
#define Swordsman_H

#include "Unit.h"

class Swordsman : public Unit {
    private:

    public:
    Swordsman(Vector3 position);
    ~Swordsman();

    // FIXME think about this.
    static char* getModelFileName() {
        return "assets/box.fbx";
    }

};

#endif