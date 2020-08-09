#ifndef PEASANT_H
#define PEASANT_H

#include "Unit.h"

class Peasant : public Unit {
    private:

    public:
    Peasant(Vector3 position);
    ~Peasant();

    // FIXME think about this.
    static char* getModelFileName() {
        return "assets/box.fbx";
    }

};

#endif