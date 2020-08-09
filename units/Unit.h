#ifndef UNIT_H
#define UNIT_H

#include <GL/glew.h>
#include <array>
#include <string>
#include <iostream>
#include "CommonTypes.h"

class Unit {
    private:
    GLuint modelBuffer;
    GLuint modelNumberOfTraingles;
    int team;
    
    protected:
    GLfloat position[4];

    std::array<GLfloat,4> velocity;

    GLfloat x() { return position[0]; }
    GLfloat y() { return position[1]; }
    GLfloat z() { return position[2]; }

    Unit(Vector3 position) {
        this->position[0] = position.x;
        this->position[1] = position.y;
        this->position[2] = position.z;
        this->position[3] = 1.0;
    }

    public:
    GLuint getModelBuffer() {
        return modelBuffer;
    }

    void setModelBuffer(GLuint modelBuffer) {
        this->modelBuffer = modelBuffer;
    }

    int getModelNumberOfTraingles() {
        return modelNumberOfTraingles;
    }

    void setModelNumberOfTraingles(int numberOfTraingles) {
        this->modelNumberOfTraingles = numberOfTraingles;
    }

    float* getPosition() {
        return position;
    }

    // FIXME, think
    virtual void updatePosition(float time) {
        position[0] += velocity[0] * time;
        position[1] += velocity[1] * time;
        // position[2] += velocity[2] * time; // FIXME, lets deal with jumping later.
    }

    virtual void updateVelocity(float time) {         // FIXME
        velocity[0] += velocity[0] * time - 0.1 > 0 ? velocity[0]* time - 0.1 : 0;
        velocity[2] += velocity[2] * time - 0.1 > 0 ? velocity[2] * time - 0.1 : 0;

        // velocity[1] += velocity[1];
    }

    void setTeam(int team) {
        this->team = team;
    }

    int getTeam() {
        return team;
    }

    #ifdef DEBUG
    void debugInfo() {
        std::cout << "info\n";
        // pos mat
        std::cout << "x: " <<  position[0] << std::endl;
        std::cout << "y: " <<  position[1] << std::endl;
        std::cout << "z: " <<  position[2] << std::endl;
        std::cout << "s: " <<  position[3] << std::endl;
        std::cout<<"\n";
        std::cout << "TEAM! " << team << std::endl; 
    }
    #endif
};

#endif