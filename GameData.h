#ifndef GameData_H
#define GameData_H

#include <array>
#include <vector>

#include "CommonTypes.h"
#include "units/Castle.h"
#include "units/Peasant.h"
#include "units/Swordsman.h"
#include "units/Archer.h"
#include "units/Tree.h"


int sizeX = 1200;
int sizeY = 600;
float right = 20;
float left = -20;
float top = 10;
float bottom = -10;
float far = -10;
float near = 10;

GLfloat postition[4] = { // FIXME, make a matrix type
   0.0f, 0.0f, 0.0f, 0.0,
};

GLfloat gaiaColour[4] = {0.0f, 1.0f, 0.0f, 1.0};
GLfloat teamOneColour[4] = {0.0f, 0.0f, 1.0f, 1.0};
GLfloat teamTwoColour[4] = {1.0f, 0.0f, 0.0f, 1.0};

struct Player {
    Player() {
        gold = 100;
    }
    
    int gold;
    Castle castle = Castle(Vector3(postition));
};

class GameData {
    private:
    std::array<Player,2> player;
    std::vector<Unit> units;
    std::vector<Tree> trees;
    
    void initializePlayer(int team, Vector3 position, VertexBufferInfo castleVertexBufferInfo) {
        Castle castle = Castle(position);
        castle.setTeam(team);
        castle.setModelBuffer(castleVertexBufferInfo.buffer);
        castle.setModelNumberOfTraingles(castleVertexBufferInfo.vertexCount/3);
        player[team].castle = castle;
    }

    public:

    Castle getCastle(int team) {
        return player[team].castle;
    }
    
    std::vector<Unit> getUnits() {
        return units;
    }

    std::vector<Tree> getTrees() {
        return trees;
    }

    void addTree(Tree tree) {
        trees.push_back(tree);
    }

    void addUnit(Unit unit) {
        units.push_back(unit);
    }

    bool buyPeasant(int team, VertexBufferInfo peasantVertexBufferInfo) {
        if (player[team].gold > 1) {
            player[team].gold--;
            Peasant peasant = Peasant(Vector3(getCastleSpawnLocation(0)));
            peasant.setTeam(0);
            peasant.setModelBuffer(peasantVertexBufferInfo.buffer);
            peasant.setModelNumberOfTraingles(peasantVertexBufferInfo.vertexCount);
            addUnit(peasant);
            return true;
        }
        return false;
    }

    float* getCastleSpawnLocation(int team){
        return player[team].castle.getPosition();
    }

    void initializeGame(VertexBufferInfo castleVertexBufferInfo) {
        Vector3 playerOneCastleStartPostition = Vector3(left, 0.0, 0.0);
        Vector3 playerTwoCastleStartPostition = Vector3(right, 0.0, 0.0);

        initializePlayer(0, playerOneCastleStartPostition, castleVertexBufferInfo);
        initializePlayer(1, playerTwoCastleStartPostition, castleVertexBufferInfo);

        units.push_back(getCastle(0));
        units.push_back(getCastle(1));
    }
};

#endif