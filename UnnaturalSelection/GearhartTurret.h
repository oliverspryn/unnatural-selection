#ifndef _GEARHARTTURRET_H             // Prevent multiple definitions if this 
#define _GEARHARTTURRET_H	          // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "terrainElement.h"
#include "projectile.h"
//need to make turret fire
class Turret : public TerrainElement
{
public:
	~Turret();
	Turret(VECTOR2 position);
	void update(float frameTime);
	Projectile** shots;
private:
};

#endif