#include <cstdio>

#include "ShaderLoader.h"
#include <GL/freeglut.h>
#include "ofbx.h"
#include <array>
#include <vector>

#include "Audio.h"
#include "units/Castle.h"
#include "CommonTypes.h"

void initialize(int argc, char** argv);
void initializeAssets();
VertexBufferInfo loadAsset(char* fileName);
void unInitializeAssets(); 
ofbx::IScene* loadFbx(char* fileName);
void display();
void keyboard(unsigned char key, int x, int y);
void initializeGame();

void buyPeasant();
void buySwordsmen();
void buyArcher();

Audio* gameSound = NULL;
GLuint basicShader;
GLuint positionHandle;
GLuint colourHandle;

int vectorIn;

VertexBufferInfo castleVertexBuffer;
std::vector<Unit> units;

GLfloat postition[4] = { // FIXME, make a matrix type
   0.0f, 0.0f, 0.0f, 0.0,
};

// FIXME, think about projections
// OpenGL clips between 1.0 and -1.0 for the different axis.
float right = 20;
float left = -20;
float top = 10;
float bottom = -10;
float far = -10;
float near = 10;

GLfloat projection[16] = { // FIXME, make a matrix type
   2.0f/(right-left),   0.0f,             0.0f,             -(right+left)/(right-left),
   0.0f,                2.0f/(top-bottom),0.0f,             -(top + bottom)/(top-bottom),
   0.0f,                0.0f,             -2.0f/(far-near), -(far + near)/(far-near),
   0.0f,                0.0f,             0.0f,             1.0f,
};

GLfloat teamOneColour[4] = {0.0f, 0.0f, 1.0f, 1.0};
GLfloat teamTwoColour[4] = {1.0f, 0.0f, 0.0f, 1.0};

int main(int argc, char** argv) {
   gameSound = new Audio();

   initialize(argc, argv);
   return 0;
}

void initialize(int argc, char** argv) {
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);

   glutInitWindowSize (1200, 600); 
   // glutFullScreen();
   glutInitWindowPosition (100, 100);
   glutCreateWindow("Castle Game");
   glewInit();

   basicShader = initShader( "shaders/vertexShader.glsl", "shaders/fragmentShader.glsl");
   glUseProgram(basicShader);

   positionHandle = glGetUniformLocation(basicShader, "position");   
   glUniform4fv(positionHandle, 1, postition);

   GLuint projectionHandle = glGetUniformLocation(basicShader, "projection");   
   glUniformMatrix4fv(projectionHandle, 1, false, projection);

   colourHandle = glGetUniformLocation(basicShader, "colour");
   glUniform4fv(colourHandle, 1, teamOneColour);

   // FIXME, probably should have a splash screen
   initializeAssets();
   initializeGame();

   vectorIn = glGetAttribLocation(basicShader, "vectorIn");
	glEnableVertexAttribArray(vectorIn);
	glVertexAttribPointer(vectorIn, 3, GL_FLOAT, GL_FALSE, 0, 0);
   
	glEnable(GL_DEPTH_TEST);

   glutDisplayFunc(display); 
   glutKeyboardFunc (keyboard);
   glutMainLoop();
}

void initializeAssets() {
   castleVertexBuffer = loadAsset(Castle::getModelFileName());
}

VertexBufferInfo loadAsset(char* fileName) {
   ofbx::IScene* assetScene = loadFbx(fileName);

   const ofbx::Geometry* assetGeometry = assetScene->getMesh(0)->getGeometry(); // will move into a objects.
   GLuint vertexBuffer;
   glGenVertexArrays(1, &vertexBuffer);
   glBindVertexArray(vertexBuffer);

   GLuint assetBuffer;
   glGenBuffers(1, &assetBuffer);
   glBindBuffer(GL_ARRAY_BUFFER, assetBuffer);
   glBufferData(GL_ARRAY_BUFFER, assetGeometry->getVertexCount(), NULL, GL_STATIC_DRAW);
   glBufferSubData(GL_ARRAY_BUFFER, 0, assetGeometry->getVertexCount(), assetGeometry->getVertices());
   VertexBufferInfo vertexBufferInfo;
   vertexBufferInfo.vertexBuffer = vertexBuffer;
   vertexBufferInfo.vertexCount = assetGeometry->getVertexCount();
   return vertexBufferInfo;
}

ofbx::IScene* loadFbx(char* fileName) {
   FILE* assetFile = fopen(fileName, "rb");
   if (!assetFile) {
      // TODO, uh oh.
   }
	fseek(assetFile, 0, SEEK_END);
	long assetFileSize = ftell(assetFile);
   fseek(assetFile, 0, SEEK_SET);
	ofbx::u8* assetFileContent = new ofbx::u8[assetFileSize];
	fread(assetFileContent, 1, assetFileSize, assetFile);
   ofbx::IScene* assetScene = ofbx::load((ofbx::u8*)assetFileContent, assetFileSize, (ofbx::u64)ofbx::LoadFlags::TRIANGULATE);
   
   delete assetFileContent;
   fclose(assetFile);
   return assetScene;
}

void unInitializeAssets() {
   // delete castleScene;
   delete gameSound;
}

void keyboard(unsigned char key, int x, int y) {
   switch (key) {
      case 27:
         unInitializeAssets();
         exit(0);
         break;

      case 1:
         buyPeasant();
         break;
      case 2:
         buySwordsmen();
         break;
      case 3:
         buyArcher();
         break;

      #ifdef DEBUG
      default:
         std::cout<< "key pressed: "  << key << "\n\n";
      #endif
   }
}

void display() {
   
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear the screen
   for (uint i = 0; i != units.size(); i++) {
      glBindVertexArray(units[i].getModelBuffer());
      units[i].debugInfo();
      glUniform4fv(positionHandle, 1, units[i].getPosition());
      if (units[i].getTeam() == 0) {
         glUniform4fv(colourHandle, 1, teamOneColour);
      } else {
         glUniform4fv(colourHandle, 1, teamTwoColour);
      }
      glDrawArrays(GL_TRIANGLES, 0 ,units[i].getModelNumberOfTraingles());
   }

   glutSwapBuffers();

}

void initializeGame() {
   Vector3 playerOneCastleStartPostition = Vector3(left, 0.0, 0.0);
   Vector3 playerTwoCastleStartPostition = Vector3(right, 0.0, 0.0);
   
   Castle playerOne = Castle(playerOneCastleStartPostition);
   playerOne.setTeam(0);
   playerOne.setModelBuffer(castleVertexBuffer.vertexBuffer);
   playerOne.setModelNumberOfTraingles(castleVertexBuffer.vertexCount);

   Castle playerTwo = Castle(playerTwoCastleStartPostition);
   playerTwo.setTeam(1);
   playerTwo.setModelBuffer(castleVertexBuffer.vertexBuffer);
   playerOne.setModelNumberOfTraingles(castleVertexBuffer.vertexCount);

   units.push_back(playerOne);
   units.push_back(playerTwo);
}

void buyPeasant() {

}

void buySwordsmen() {

}

void buyArcher() {
   
}