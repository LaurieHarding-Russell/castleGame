#ifndef COMMON_TYPES_H
#define COMMON_TYPES_H

#include <GL/glew.h>
#include <array>

struct VertexBufferInfo {
   GLuint vertexBuffer;
   int vertexCount;
};

struct Vector3 {
   GLfloat x;
   GLfloat y;
   GLfloat z;

   Vector3(GLfloat x, GLfloat y, GLfloat z) {
      this->x = x;
      this->y = y;
      this->z = z;
   }

   float* toFloatArray() {
      return new float[3]{x, y, z};
   }
};

struct Vector4 {
   GLfloat x;
   GLfloat y;
   GLfloat z;
   GLfloat scale;

   Vector4() {}

   Vector4(GLfloat x, GLfloat y, GLfloat z, GLfloat scale) {
      this->x = x;
      this->y = y;
      this->z = z;
      this->scale = scale;
   }

   float* toFloatArray() {
      return new float[4]{x, y, z, scale};
   }
};

struct Matrix4 {
   std::array<Vector4, 4> vectors;

   // FIXME, think about this.
   Matrix4(Vector4 Vector0, Vector4 Vector1, Vector4 Vector2, Vector4 Vector3) {
      vectors[0] = Vector0;
      vectors[1] = Vector1;
      vectors[2] = Vector2;
      vectors[3] = Vector3;
   }

   float* toFloatArray() {
      float* result = new float[16];
      for(int i = 0; i != 4; i++) {
         float* floatArray = vectors[i].toFloatArray();
         std::copy(vectors[0].toFloatArray(), floatArray + 4, result + 4 * i);
      }
      return result;
   }
};

#endif