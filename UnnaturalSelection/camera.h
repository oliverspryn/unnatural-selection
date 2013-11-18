//The is the camera interface
//By Michael Wiegand
// 11/8/2013

#ifndef CAMERA_H
#define CAMERA_H
#define WIN32_LEAN_AND_MEAN
#include "entity.h"

class Camera
{
public:
	Camera(int width, int height, int xReal, int yReal, int x, int y, float zoom);
	void draw(Image in);
	void draw(Image in, DWORD tint);
	void draw(Image in, DWORD tint, bool hoizontalFlip, bool virticalFlip);
	void draw(Entity& in);
	void draw(Entity& in, bool hoizontalFlip, bool virticalFlip);
	D3DXVECTOR2 getRealPos(float x, float y);
	D3DXVECTOR2 getCameraRelitivePos(float x, float y);
	D3DXVECTOR2 centerPosition;
	D3DXVECTOR2 realPosition;
	int height;
	int width;
	float zoom;
	

};




#endif