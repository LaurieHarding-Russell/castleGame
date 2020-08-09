#ifndef Tree_H
#define Tree_H

#include "Unit.h"

class Tree : public Unit {
    private:

    public:
    Tree(Vector3 position);
    ~Tree();

    // FIXME think about this.
    static const char* getModelFileName() {
        return "assets/box.fbx";
    }

};

#endif