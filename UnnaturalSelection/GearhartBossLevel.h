#ifndef __GEARHARTBOSSLEVEL_H
#define __GEARHARTBOSSLEVELP_H
#define WIN32_LEAN_AND_MEAN

#include "LMap.h"

class BossLevel : public LMap
{
public:
	bool pressed;
	BossLevel(Input* i, Graphics* g);
	bool initialize(Game *gamePtr, int width, int height, int ncols, TextureManager *textureM, TextureManager *targetTM, TextureManager *turretTM, Magazine* m);
	void update(float frameTime);
private:
};

#endif