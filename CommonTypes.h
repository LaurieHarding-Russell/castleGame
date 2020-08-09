#include <GL/glew.h>

#ifndef COMMON_TYPES_H
#define COMMON_TYPES_H

struct VertexBufferInfo {
   GLuint vertexBuffer;
   int vertexCount;
};

struct Vector3 {
   Vector3(GLfloat x, GLfloat y, GLfloat z) {
      this->x = x;
      this->y = y;
      this->z = z;
   }
   GLfloat x;
   GLfloat y;
   GLfloat z;
};

#endif