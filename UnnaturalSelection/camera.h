//The is the camera interface
//By Michael Wiegand
// 11/8/2013

#ifndef CAMERA_H
#define CAMERA_H
#define WIN32_LEAN_AND_MEAN
#include "image.h"

class Camera
{
public:
	Camera(int width, int height, int xReal, int yReal, int x, int y, float zoom);
	void draw(Image in);

	D3DXVECTOR2 centerPosition;
	D3DXVECTOR2 realPosition;
	int height;
	int width;
	float zoom;


};




#endif