#ifndef _GEARHARTTURRET_H             // Prevent multiple definitions if this 
#define _GEARHARTTURRET_H	          // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "terrainElement.h"
#include "gun.h"
#include "Character.h"
//need to make turret fire
class Turret : public TerrainElement
{
public:
	~Turret();
	Turret(VECTOR2 position, Gun* g,Magazine* m,Character* c);
	void update(float frameTime);
	Gun* gun;
	Character* target;
	int direction;
	int fireTime;
private:
};

#endif