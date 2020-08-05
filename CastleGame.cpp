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
void reshape (int w, int h);

ofbx::IScene* castleScene = nullptr;
Audio* gameSound = NULL;

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

   glutDisplayFunc(display); 
   glutReshapeFunc(reshape);
   glutKeyboardFunc (keyboard);

   glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_DEPTH_TEST);

   glewInit();

   GLuint programID = initShader( "shaders/vertexShader.glsl", "shaders/fragmentShader.glsl");

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
	auto* castleAssetFileContent = new ofbx::u8[castleAssetFileSize];
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
   const ofbx::Object* castle = castleScene->getRoot();

   // int vertexBuffer;
   // glGenVertexArrays(1, &vertexBuffer);
   // glBindVertexArray(vertexBuffer);

   // int buffer;
   // glGenBuffers(1, &buffer);
   // glBindBuffer(GL_ARRAY_BUFFER, buffer);
   // glBufferData(GL_ARRAY_BUFFER, castle.getVertexCount(), castle.getVertices(), GL_STATIC_DRAW);
   // glClear(GL_COLOR_BUFFER_BIT);
   // glDrawArrays(GL_POINTS, 0, N);
   // glFlush();

}

void reshape (int w, int h) {
   glViewport (0, 0, (GLsizei) w, (GLsizei) h);
}