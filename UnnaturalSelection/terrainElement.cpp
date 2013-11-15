#include "terrainElement.h"

TerrainElement::TerrainElement()
{
	collisionType = entityNS::BOX;
	mass = terrainNS::MASS;
}

void TerrainElement::generateSideEquations()
{
	corners[3] = VECTOR2(this->getCenterX() + cos(this->getRadians())*edge.right - sin(this->getRadians())*edge.top, this->getCenterY() + cos(this->getRadians())*edge.top + sin(this->getRadians())*edge.right);
	corners[2] = VECTOR2(this->getCenterX() + cos(this->getRadians())*edge.right - sin(this->getRadians())*edge.bottom, this->getCenterY() + cos(this->getRadians())*edge.bottom + sin(this->getRadians())*edge.right);
	corners[1] = VECTOR2(this->getCenterX() + cos(this->getRadians())*edge.left - sin(this->getRadians())*edge.bottom, this->getCenterY() + cos(this->getRadians())*edge.bottom + sin(this->getRadians())*edge.left);
	corners[0] = VECTOR2(this->getCenterX() + cos(this->getRadians())*edge.left - sin(this->getRadians())*edge.top, this->getCenterY() + cos(this->getRadians())*edge.top + sin(this->getRadians())*edge.left);
	for(int i(0); i < 4; i++)
	{
		D3DXVECTOR2 tempDist = corners[(3+i)%4]-corners[i];
		sides[i] = myLines::Ray(corners[i], tempDist, (i%2?getHeight():getWidth()));
	}
	
	/*sides[0] = myLines::Ray(corners[0], corners[3]-corners[0],this->getWidth());
	sides[1] = myLines::Ray(corners[1], corners[0]-corners[1],this->getHeight());
	sides[2] = myLines::Ray(corners[2], corners[2]-corners[1],this->getWidth());
	sides[3] = myLines::Ray(corners[3], corners[3]-corners[2],this->getHeight());*/
}

float TerrainElement::getXCorner(float m1, float b1, float m2, float b2)
{
	return ((b2-b1)/(m1-m2));
}

bool TerrainElement::initialize(Game* gPtr, TextureManager* texture, int nCol)
{
	generateSideEquations();
	return Entity::initialize(gPtr,spriteData.width,spriteData.height,nCol,texture);
}

bool TerrainElement::initialize(Game *gamePtr, int width, int height, int ncols, TextureManager *textureM)
{
	return Entity::initialize(gamePtr,width,height,ncols,textureM);
}

StraightPath::StraightPath(int height, int width, VECTOR2 center) : TerrainElement()
{
	spriteData.height = height;
	spriteData.width = width;
	spriteData.x = center.x;
	spriteData.y = center.y;
	edge.left = (width/2)*-1;
	edge.right = width/2;
	edge.top = (height/2)*-1;
	edge.bottom = (height/2);
	mass = terrainNS::MASS;
}

SlantedPath::SlantedPath(int height, int width, VECTOR2 center)
{
	spriteData.height = height;
	spriteData.width = width;
	spriteData.x = center.x;
	spriteData.y = center.y;
	edge.left = (width/2)*-1;
	edge.right = width/2;
	edge.top = (height/2)*-1;
	edge.bottom = (height/2);
	mass = terrainNS::MASS;
}

void SlantedPath::collide(Entity* ent)
{
	//ent->setVelocity(D3DXVECTOR2(ent->getVelocity().x,0));
}

void StraightPath::collide(Entity* ent)
{
	ent->setVelocity(D3DXVECTOR2(ent->getVelocity().x,0));
}

Wall::Wall(int height, int width, VECTOR2 center) : TerrainElement()
{
	spriteData.height = height;
	spriteData.width = width;
	spriteData.x = center.x;
	spriteData.y = center.y;
	edge.left = (width/2)*-1;
	edge.right = width/2;
	edge.top = (height/2)*-1;
	edge.bottom = (height/2);
}

void Wall::collide(Entity* ent)
{
	ent->setVelocity(VECTOR2(0,ent->getVelocity().y));
	if(ent->getCenterX() < getCenterX())
	{
		ent->setX((getCenterX()-(getWidth()+ent->getWidth())/2)-ent->getWidth()/2);
	}else{
		ent->setX((getCenterX()+(getWidth()-ent->getWidth())/2)+ent->getWidth()/2);				
	}
}

bool TerrainElement::collidesWithRay(myLines::Ray* in, float& frameTime)
{
	float fT = frameTime;
	bool collide = false;
	for(int i = 0; i < 4; i++)
	{
		if(in->getTimeOfIntersectRay(sides[i],fT))
		{
			collide = true;
		}
	}
	frameTime = fT;
	return collide;
}