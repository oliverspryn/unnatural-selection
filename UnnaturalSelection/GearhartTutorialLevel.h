#ifndef _GEARHARTTUTORIALLEVEL_H             // Prevent multiple definitions if this 
#define _GEARHARTTUTORIALLEVEL_H	          // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "LMap.h"
#include "GearhartTurret.h"

class TutorialLevel : public LMap
{
public:
	TutorialLevel(Input* i, Graphics* g);
	bool initialize(Game *gamePtr, int width, int height, int ncols, TextureManager *textureM, TextureManager *targetTM, TextureManager *turretTM);
	void update(float frameTime);
	void draw();
	TerrainElement** doors;
	Turret** turrets;
	int numDoors;
	int currentDoor;
	int numTurrets;
	int room2TurretsKilled;
private:
};

#endif