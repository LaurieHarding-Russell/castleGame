#ifndef CASTLE_H
#define CASTLE_H

#include "Unit.h"

class Castle : public Unit {
    private:

    public:
    Castle(std::array<GLfloat,3> position);
    ~Castle();


    // FIXME think about this.
    static char* getModelFileName() {
        return "assets/box.fbx";
    }

};

#endif