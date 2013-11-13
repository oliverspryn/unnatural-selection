#include "terrainElement.h"

TerrainElement::TerrainElement()
{
	collisionType = entityNS::BOX;
	mass = terrainNS::MASS;
}

void TerrainElement::generateSideEquations()
{
	m[0] = sin(this->getRadians())/cos(this->getRadians());
	m[1] = sin(this->getRadians()+PI/2)/cos(this->getRadians()+PI/2);
	m[2] = sin(this->getRadians()+PI)/cos(this->getRadians()+PI);
	m[3] = sin(this->getRadians()+3*PI/2)/cos(this->getRadians()+3*PI/2);

	float x = this->getCenterX() + cos(this->getRadians()+PI/2)*edge.top;
	float y = this->getCenterY() + sin(this->getRadians()+PI/2)*edge.top;
	b[0] = y - m[0]*x;

	x = this->getCenterX() + cos(this->getRadians()+PI)*edge.right;
	y = this->getCenterY() + sin(this->getRadians()+PI)*edge.right;
	b[1] = y - m[1]*x;

	x = this->getCenterX() + cos(this->getRadians()+3*PI/2)*edge.top;
	y = this->getCenterY() + sin(this->getRadians()+3*PI/2)*edge.top;
	b[2] = y - m[2]*x;

	x = this->getCenterX() + cos(this->getRadians())*edge.right;
	y = this->getCenterY() + sin(this->getRadians())*edge.right;
	b[3] = y - m[3]*x;

	/*for(int i = 0; i < 4; i++)
	{
		float x = getXCorner(m[i],b[i],m[(i+1)%4],b[(i+1)%4]);
		corners[i] = VECTOR2(x, m[i]*x+b[i]);
	}*/
	corners[3] = VECTOR2(this->getCenterX() + cos(this->getRadians())*edge.right - sin(this->getRadians())*edge.top, this->getCenterY() + cos(this->getRadians())*edge.top + sin(this->getRadians())*edge.right);
	corners[2] = VECTOR2(this->getCenterX() + cos(this->getRadians())*edge.right - sin(this->getRadians())*edge.bottom, this->getCenterY() + cos(this->getRadians())*edge.bottom + sin(this->getRadians())*edge.right);
	corners[1] = VECTOR2(this->getCenterX() + cos(this->getRadians())*edge.left - sin(this->getRadians())*edge.bottom, this->getCenterY() + cos(this->getRadians())*edge.bottom + sin(this->getRadians())*edge.left);
	corners[0] = VECTOR2(this->getCenterX() + cos(this->getRadians())*edge.left - sin(this->getRadians())*edge.top, this->getCenterY() + cos(this->getRadians())*edge.top + sin(this->getRadians())*edge.left);

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
}