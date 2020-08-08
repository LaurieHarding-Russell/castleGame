#ifndef UNIT_H
#define UNIT_H

#include <GL/glew.h>
#include <array>
#include <string>
#include <iostream>

class Unit {
    private:
    GLuint modelBuffer;
    GLuint modelNumberOfTraingles;
    int team;
    
    protected:
    std::array<GLfloat,4> position;
    GLfloat positionMatrix[16] = { // FIXME, make a matrix type
      1.0f, 0.0f, 0.0f, 0.0,
      0.0f, 1.0f, 0.0f, 0.0,
      0.0f, 0.0f, 1.0f, 0.0,
      0.0f, 0.0f, 0.0f, 1.0,
   };

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
        positionMatrix[0] = position[0];
        positionMatrix[5] = position[1];
        positionMatrix[10] = position[2];
        positionMatrix[15] = position[3];
        return positionMatrix;
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
        std::cout << "y: " <<  position[0] << std::endl;
        std::cout << "z: " <<  position[0] << std::endl;
        std::cout << "s: " <<  position[0] << std::endl;
        std::cout<<"\n";
        GLfloat* mat = getPositionMatrix();
        std::cout<<"Pos Mat \n";
        for (int i = 0; i != 4; i++) {
            std::cout << "[ ";
            for (int j = 0; j != 4; j++) {
                std::cout <<  mat[i*4 + j] << ",";
            }
            std::cout << " ]\n";
        }
    }
    #endif
};

#endif