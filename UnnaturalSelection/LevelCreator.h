#ifndef _LEVELCREATOR_H
#define _LEVELCREATOR_H

#include "game.h"
#include "textureManager.h"
#include "textDX.h"
#include "LMap.h"
#include "textDX.h"
#include <vector>
using std::vector;
#include <cstdlib>
#include <sstream>
using std::stringstream;
//#include "terrainElement.h"


class LevelCreator : public Game
{
public:
	LevelCreator();

	//destructor
	~LevelCreator();

	// Initialize the game
    void initialize(HWND hwnd);
    void update();      // must override pure virtual from Game
    void ai();          // "
    void collisions();  // "
    void render();      // "
    void releaseAll();
    void resetAll();
	void consoleCommand();
	TextDX* mousePoint;
private:
	int blockMoveX,blockMoveY;
	int totalTarget, targetToPrint;
	void buildFromFile(std::string fileName);
	TerrainElement* movingObject;
	bool clicked, prevClick;
	bool targetSelected;
	TerrainElement* findEntityByClick(int x, int y, bool& found);
	int selectedTerrain;
	int terrainNumToPrint,spawnNumToPrint;//used int outputting to file
	int totalTerrain;
	bool getHeight, getWidth, moveObject;
	bool saveFile;
	bool objectChosen;
	DWORD oldColor;
	int boxHeight, boxWidth;
	int a,r,g,b;
	TextureManager terrainTexture, targetTexture;
	LMap* testMap;
	bool multipleBlocks, firstBlock;
	bool loadFile;
	bool chooseA, chooseR, chooseG, chooseB;
	bool addSpawn;
	bool spawnChosen;
	bool chooseHealth;
};

#endif