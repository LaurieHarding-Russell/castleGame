#include <cstdio>

#include "ShaderLoader.h"
#include <GL/freeglut.h>
#include "ofbx.h"

#include "Audio.h"

void initializeWindow(int argc, char** argv);
void initializeAssets();
void unInitializeAssets();
void display();
void keyboard(unsigned char key, int x, int y);

ofbx::IScene* castleScene = nullptr;
Audio* gameSound = NULL;
GLuint basicShader;

float camera[16];

int main(int argc, char** argv) {
   gameSound = new Audio();

   bool running = true;

   initializeAssets();
   initializeWindow(argc, argv);

   do {
      
   } while(running);

   unInitializeAssets();
   delete gameSound;
   return 0;
}

void initializeWindow(int argc, char** argv) {
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);

   glutInitWindowSize (1280, 600); 
   // glutFullScreen();
   glutInitWindowPosition (100, 100);
   glutCreateWindow("Castle Game");
   glewInit();

   const ofbx::Geometry* castleGeometry = castleScene->getMesh(0)->getGeometry(); // will move into a objects.

   float verts[]={
      // triangle 1
      -1.0f,-1.0f, 0.0f, 1.0f,						// bottom left
      -1.0f,1.0f, .0f, 1.0f,						// Top left
      1.0f,1.0f, .0f, 1.0f,						// top right
      // triangle 2
      -1.0f,-1.0f, .0f, 1.0f,						// bottom left
      1.0f,1.0f, .0f, 1.0f,						// top right
      1.0f,-1.0f, .0f, 1.0f						// bottom right
   };
   
   basicShader = initShader( "shaders/vertexShader.glsl", "shaders/fragmentShader.glsl");
   glUseProgram(basicShader);

   GLuint vao; // FIXME
   glGenVertexArrays(1, &vao);
   glBindVertexArray(vao);

   GLuint buffer;
   glGenBuffers(1, &buffer);
   glBindBuffer(GL_ARRAY_BUFFER, buffer);
   // glBufferData(GL_ARRAY_BUFFER, castleGeometry->getVertexCount(), castleGeometry->getVertices(), GL_STATIC_DRAW);
   glBufferData(GL_ARRAY_BUFFER, castleGeometry->getVertexCount(), NULL, GL_STATIC_DRAW);
   glBufferSubData(GL_ARRAY_BUFFER, 0, castleGeometry->getVertexCount(), castleGeometry->getVertices());

   // GLuint projectionHandle = glGetUniformLocation(basicShader, "Projection");
   // glUniformMatrix4dv(projectionHandle, 1, false, camera);

   int vectorIn = glGetAttribLocation(basicShader, "vectorIn");
	glEnableVertexAttribArray(vectorIn);
	glVertexAttribPointer(vectorIn, 3, GL_FLOAT, GL_FALSE, 0, 0);
   
	glEnable(GL_DEPTH_TEST);

   glutDisplayFunc(display); 
   glutKeyboardFunc (keyboard);
   glutMainLoop();
}

void initializeAssets() {
   FILE* castleAssetFile = fopen("assets/box.fbx", "rb");
   if (!castleAssetFile) {
      // TODO, uh oh.
   }
	fseek(castleAssetFile, 0, SEEK_END);
	long castleAssetFileSize = ftell(castleAssetFile);
   fseek(castleAssetFile, 0, SEEK_SET);
	ofbx::u8* castleAssetFileContent = new ofbx::u8[castleAssetFileSize];
	fread(castleAssetFileContent, 1, castleAssetFileSize, castleAssetFile);
   castleScene = ofbx::load((ofbx::u8*)castleAssetFileContent, castleAssetFileSize, (ofbx::u64)ofbx::LoadFlags::TRIANGULATE);
   
   delete castleAssetFileContent;
   fclose(castleAssetFile);
}

void unInitializeAssets() {
   // delete castleScene;
}

void keyboard(unsigned char key, int x, int y)
{
   switch (key) {
      case 27:
         exit(0);
         break;
   }
}

void display() {
   
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear the screen

   glDrawArrays(GL_TRIANGLES, 0 ,6);
   glutSwapBuffers();

}