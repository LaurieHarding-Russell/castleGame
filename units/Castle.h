#ifndef CASTLE_H
#define CASTLE_H

#include "Unit.h"

class Castle : public Unit {
    private:

    public:
    Castle(Vector3 position);
    ~Castle();


    // FIXME think about this.
    static const char* getModelFileName() {
        return "assets/box.fbx";
    }

};

#endif