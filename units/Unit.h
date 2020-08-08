#ifndef UNIT_H
#define UNIT_H

#include <GL/glew.h>
#include <array>
#include <string>

class Unit {
    private:
    GLuint modelBuffer;
    GLuint modelNumberOfTraingles;
    int team;
    
    protected:
    std::array<GLfloat,4> position;
    
    std::array<GLfloat,4> velocity;

    GLfloat x() { return position[0]; }
    GLfloat y() { return position[1]; }
    GLfloat z() { return position[2]; }

    Unit(std::array<GLfloat,3> position) {
        this->position[0] = position[0];
        this->position[1] = position[1];
        this->position[2] = position[2];
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

    std::array<float,4> getPosition() {
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

    virtual GLfloat* getPositionMatrix() {
        GLfloat positionMatrix[] = { // FIXME, make a matrix type
            position[0], 0.0f, 0.0f, 0.0,
            0.0f, position[1], 0.0f, 0.0,
            0.0f, 0.0f, position[2], 0.0,
            0.0f, 0.0f, 0.0f, position[3],
        };
        return positionMatrix;
    }

    void setTeam(int team) {
        this->team = team;
    }
};

#endif