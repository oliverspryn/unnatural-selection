#ifndef _GEARHARTARENALEVEL_H             // Prevent multiple definitions if this 
#define _GEARHARTARENALEVEL_H	          // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "LMap.h"

class ArenaLevel : public LMap
{
public:
	ArenaLevel(Input* i, Graphics* g, int numKills=30);
	bool initialize(Game *gamePtr, int width, int height, int ncols, TextureManager *textureM, TextureManager *targetTM, TextureManager *turretTM, Magazine* m);
	void update(float frameTime);
	int killsToWin;
	int totalKills;
};

#endif