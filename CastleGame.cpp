#include <cstdio>

#include "ShaderLoader.h"
#include <GL/freeglut.h>
#include "ofbx.h"
#include <array>
#include <vector>
#include <chrono>
#include <random>
#include <ctime>

#include "Audio.h"
#include "units/Castle.h"
#include "units/Peasant.h"
#include "units/Swordsman.h"
#include "units/Archer.h"
#include "units/Tree.h"
#include "CommonTypes.h"

using namespace std::chrono;

void initialize(int argc, char** argv);
void initializeAssets();
VertexBufferInfo loadAsset(const char* fileName);
void unInitializeAssets(); 
ofbx::IScene* loadFbx(const char* fileName);

void display();
void keyboard(unsigned char key, int x, int y);
void gameProcess();

void initializeGame();
void createUnit();
void generateMap();

void buyPeasant();
void buySwordsmen();
void buyArcher();

Audio* gameSound = NULL;
GLuint basicShader;
GLuint positionHandle;
GLuint colourHandle;

int vectorIn;

milliseconds lastUpdatedTime;
milliseconds timeSinceLastTreeGenerationTry = duration_cast< milliseconds >(system_clock::now().time_since_epoch());

// FIXME, you guessed it think about this.
VertexBufferInfo castleVertexBuffer;
VertexBufferInfo peasantVertexBuffer;
VertexBufferInfo swordsmanVertexBuffer;
VertexBufferInfo archerVertexBuffer;
VertexBufferInfo treeVertexBuffer;
VertexBufferInfo mapVertexBuffer;


// FIXME, think about this.
std::vector<Unit> units;
std::vector<Tree> trees;

GLfloat postition[4] = { // FIXME, make a matrix type
   0.0f, 0.0f, 0.0f, 0.0,
};

// FIXME, think about projections
// OpenGL clips between 1.0 and -1.0 for the different axis.
int sizeX = 1200;
int sizeY = 600;
float right = 20;
float left = -20;
float top = 10;
float bottom = -10;
float far = -10;
float near = 10;

GLfloat projection[16] = { // FIXME, make a matrix type
   2.0f/(right-left),   0.0f,             0.0f,             -((right+left)/(right-left)),
   0.0f,                2.0f/(top-bottom),0.0f,             -((top + bottom)/(top-bottom)),
   0.0f,                0.0f,             -2.0f/(far-near), -((far + near)/(far-near)),
   0.0f,                0.0f,             0.0f,             1.0f,
};

GLfloat gaiaColour[4] = {0.0f, 1.0f, 0.0f, 1.0};
GLfloat teamOneColour[4] = {0.0f, 0.0f, 1.0f, 1.0};
GLfloat teamTwoColour[4] = {1.0f, 0.0f, 0.0f, 1.0};

int main(int argc, char** argv) {
   srand (std::time(NULL));
   gameSound = new Audio();

   initialize(argc, argv);
   return 0;
}

void initialize(int argc, char** argv) {
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);

   glutInitWindowSize (sizeX, sizeY); 
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
   glutIdleFunc(gameProcess);

   lastUpdatedTime = duration_cast< milliseconds >(system_clock::now().time_since_epoch());
   glutMainLoop();
}

void initializeAssets() {
   GLuint vertexBuffer;
   glGenVertexArrays(1, &vertexBuffer);
   glBindVertexArray(vertexBuffer);

   castleVertexBuffer = loadAsset(Castle::getModelFileName());
   peasantVertexBuffer = loadAsset(Peasant::getModelFileName());
   swordsmanVertexBuffer = loadAsset(Swordsman::getModelFileName());
   archerVertexBuffer = loadAsset(Archer::getModelFileName());
   treeVertexBuffer = loadAsset(Tree::getModelFileName());

   // generateMap();
}

VertexBufferInfo loadAsset(const char* fileName) {
   ofbx::IScene* assetScene = loadFbx(fileName);

   const ofbx::Geometry* assetGeometry = assetScene->getMesh(0)->getGeometry(); // will move into a objects.

   GLuint assetBuffer;
   glGenBuffers(1, &assetBuffer);
   glBindBuffer(GL_ARRAY_BUFFER, assetBuffer);
   glBufferData(GL_ARRAY_BUFFER, assetGeometry->getVertexCount() * 3, NULL, GL_STATIC_DRAW);
   glBufferSubData(GL_ARRAY_BUFFER, 0, assetGeometry->getVertexCount() * 3, assetGeometry->getVertices());
   VertexBufferInfo vertexBufferInfo;
   vertexBufferInfo.buffer = assetBuffer;
   vertexBufferInfo.vertexCount = assetGeometry->getVertexCount();
   return vertexBufferInfo;
}

ofbx::IScene* loadFbx(const char* fileName) {
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

      case '1':
         buyPeasant();
         break;
      case '2':
         buySwordsmen();
         break;
      case '3':
         buyArcher();
         break;

      #ifdef DEBUG
      default:
         std::cout<< "key pressed: "  << int(key) << "\n\n";
      #endif
   }
}

void display() {
   
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear the screen

   glBindBuffer(GL_ARRAY_BUFFER, mapVertexBuffer.buffer);
   glUniform4fv(colourHandle, 1, gaiaColour);
   glUniform4fv(positionHandle, 1, postition);
   glDrawArrays(GL_TRIANGLES, 0 , (mapVertexBuffer.vertexCount/3)/3);

   for (uint i = 0; i != units.size(); i++) {
      glBindBuffer(GL_ARRAY_BUFFER, units[i].getModelBuffer());
      // units[i].debugInfo();
      glUniform4fv(positionHandle, 1, units[i].getPosition());
      if (units[i].getTeam() == 0) {
         glUniform4fv(colourHandle, 1, teamOneColour);
      } else {
         glUniform4fv(colourHandle, 1, teamTwoColour);
      }
      glDrawArrays(GL_TRIANGLES, 0 , units[i].getModelNumberOfTraingles());
   }

   for (uint i = 0; i != trees.size(); i++) {
      glBindBuffer(GL_ARRAY_BUFFER, trees[i].getModelBuffer());
      glUniform4fv(positionHandle, 1, trees[i].getPosition());
      glUniform4fv(colourHandle, 1, gaiaColour);

      glDrawArrays(GL_TRIANGLES, 0 , units[i].getModelNumberOfTraingles());
   }

   glutSwapBuffers();

}

void gameProcess() {
   milliseconds currentTime = duration_cast< milliseconds >(system_clock::now().time_since_epoch());
   milliseconds timeDiff = lastUpdatedTime - currentTime;

   if ((currentTime - timeSinceLastTreeGenerationTry).count() > 5000) {
      float x = (rand() % 20) + left + 10;
      float y = 0;
      Tree tree = Tree({ x, y, 0});
      tree.setTeam(-1);
      tree.setModelBuffer(treeVertexBuffer.buffer);
      tree.setModelNumberOfTraingles(treeVertexBuffer.vertexCount);

      trees.push_back(tree);
      timeSinceLastTreeGenerationTry = currentTime;
   }

   // update unit positions and velocity

   lastUpdatedTime = currentTime;

}


void initializeGame() {
   Vector3 playerOneCastleStartPostition = Vector3(left, 0.0, 0.0);
   Vector3 playerTwoCastleStartPostition = Vector3(right, 0.0, 0.0);
   
   Castle playerOne = Castle(playerOneCastleStartPostition);
   playerOne.setTeam(0);
   playerOne.setModelBuffer(castleVertexBuffer.buffer);
   playerOne.setModelNumberOfTraingles(castleVertexBuffer.vertexCount);

   Castle playerTwo = Castle(playerTwoCastleStartPostition);
   playerTwo.setTeam(1);
   playerTwo.setModelBuffer(castleVertexBuffer.buffer);
   playerOne.setModelNumberOfTraingles(castleVertexBuffer.vertexCount);

   units.push_back(playerOne);
   units.push_back(playerTwo);
}

void buyPeasant() {
   // gameSound->buySucces();
   gameSound->buyFail();
}

void buySwordsmen() {
   gameSound->buyFail();
}

void buyArcher() {
   gameSound->buyFail();
}

void createUnit() {

}

// Might make this generate a bumpier map with terrian.
void generateMap() {
   mapVertexBuffer.vertexCount = 36;

   float mapData[36] = {
      left, 0.0, 0.0,
      right, 0.0, 0.0,
      left, 0.0, 5.0,

      left, 0.0, 5.0,
      right, 0.0, 0.0,
      right, 0.0, 5.0,

      left, 0.0, 0.0,
      right, 1.0, 0.0,
      left, 1.0, 0.0,
      
      left, 0.0, 0.0,
      right, 0.0, 0.0,
      right, 1.0, 0.0
   };

   glGenBuffers(1, &mapVertexBuffer.buffer);
   glBindBuffer(GL_ARRAY_BUFFER, mapVertexBuffer.buffer);
   glBufferData(GL_ARRAY_BUFFER, mapVertexBuffer.vertexCount, NULL, GL_STATIC_DRAW);
   glBufferSubData(GL_ARRAY_BUFFER, 0, mapVertexBuffer.vertexCount, mapData);

}