#ifndef CASTLE_H
#define CASTLE_H

#include "Unit.h"

class Castle : public Unit {
    private:

    public:
    Castle(std::array<float,3> position);
    ~Castle();


    // FIXME think about this.
    static std::string getModelFileName() {
        return "assets/box.fbx";
    }

    static GLuint modelBuffer;

};

#endif