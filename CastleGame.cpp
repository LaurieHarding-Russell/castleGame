#include <cstdio>

#include "ShaderLoader.h"
#include <GL/freeglut.h>
#include "ofbx.h"
#include <array>
#include <vector>

#include "Audio.h"
#include "units/Castle.h"

struct VertexBufferInfo {
   GLuint vertexBuffer;
   int vertexCount;
};

void initialize(int argc, char** argv);
void initializeAssets();
VertexBufferInfo loadAsset(char* fileName);
void unInitializeAssets(); 
void display();
void keyboard(unsigned char key, int x, int y);
void initializeGame();

Audio* gameSound = NULL;
GLuint basicShader;
GLuint positionHandle;
GLuint colourHandle;

int vectorIn;

VertexBufferInfo castleVertexBuffer;
std::vector<Unit> units;

GLfloat postition[16] = { // FIXME, make a matrix type
   1.0f, 0.0f, 0.0f, 0.0,
   0.0f, 1.0f, 0.0f, 0.0,
   0.0f, 0.0f, 1.0f, 0.0,
   0.0f, 0.0f, 0.0f, 1.0,
};

GLfloat orthographicProjection[16] = { // FIXME, make a matrix type
   1.0f, 0.0f, 0.0f, 0.0,
   0.0f, 1.0f, 0.0f, 0.0,
   0.0f, 0.0f, 0.0f, 0.0,
   0.0f, 0.0f, 0.0f, 1.0,
};

GLfloat teamOneColour[4] = {0.0f, 0.0f, 1.0f, 1.0};
GLfloat teamTwoColour[4] = {1.0f, 0.0f, 0.0f, 1.0};

int main(int argc, char** argv) {
   gameSound = new Audio();

   initialize(argc, argv);

   // FIXME, probably should uninitialize things.. I know OS does it for me.
   // unInitializeAssets();
   // delete gameSound;
   return 0;
}

void initialize(int argc, char** argv) {
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);

   glutInitWindowSize (1280, 600); 
   // glutFullScreen();
   glutInitWindowPosition (100, 100);
   glutCreateWindow("Castle Game");
   glewInit();

   basicShader = initShader( "shaders/vertexShader.glsl", "shaders/fragmentShader.glsl");
   glUseProgram(basicShader);

   positionHandle = glGetUniformLocation(basicShader, "position");   
   glUniformMatrix4fv(positionHandle, 1, false, postition);

   GLuint projectionHandle = glGetUniformLocation(basicShader, "projection");   
   glUniformMatrix4fv(projectionHandle, 1, false, orthographicProjection);

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

   for (uint i = 0; i != units.size(); i++) {
      glBindVertexArray(units[i].getModelBuffer());
      units[i].getPositionMatrix();
      glUniformMatrix4fv(positionHandle, 1, false, units[i].getPositionMatrix());
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
   std::array<GLfloat,3> playerOneCastleStartPostition = {1.0, 1.0, 1.0};
   std::array<GLfloat,3> playerTwoCastleStartPostition = {-1.0, 1.0, 1.0};
   
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