#ifndef _GEARHARTTURRET_H             // Prevent multiple definitions if this 
#define _GEARHARTTURRET_H	          // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "terrainElement.h"
#include "gun.h"
#include "Character.h"
//need to make turret fire
enum turretPattern {FOLLOW,HORIZONTAL,CHASE};
class Turret : public TerrainElement
{
public:
	~Turret();
	Turret(int height,int width,VECTOR2 position, Gun* g,Magazine* m,Character* c,turretPattern mo = HORIZONTAL);
	void update(float frameTime,bool fire);
	Gun* gun;
	Character* target;
	int direction;
	int yDirection;
	int fireTime;
	int sight;
	turretPattern motion;
private:
};

#endif