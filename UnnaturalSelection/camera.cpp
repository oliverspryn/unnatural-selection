//This is the implementation of camera
//By Michael Wiegand 
// 11/8/2013
#include "camera.h"

Camera::Camera(int width, int height, int xReal, int yReal, int x, int y, float zoom): width(width), height(height), realPosition(xReal, yReal), centerPosition(x, y), zoom(zoom)
{
	
}
void Camera::draw(Image in)
{
	if(in.getVisible())
	{
		//Checks x
		if(centerPosition.x + (width/2)/zoom > in.getX() && centerPosition.x - (width/2)/zoom < in.getX()+in.getWidth()*in.getScaleX())
		{
			//Checks y
			if(centerPosition.y + (height/2)/zoom > in.getY() && centerPosition.y - (height/2)/zoom < in.getY()+in.getHeight()*in.getScaleY())
			{
				float relX = (in.getCenterX()-centerPosition.x)*zoom;
				float relY = (in.getCenterY()-centerPosition.y)*zoom;
				in.setScaleX(in.getScaleX()*zoom);
				in.setScaleY(in.getScaleY()*zoom);
				in.setX(realPosition.x + relX + (width/2) - in.getScaleX()*in.getWidth()/2);
				in.setY(realPosition.y + relY + (height/2) - in.getScaleY()*in.getHeight()/2);

				in.draw();
			}
		}
	}
}
void Camera::draw(Image in, DWORD tint)
{
	if(in.getVisible())
	{
		//Checks x
		if(centerPosition.x + (width/2)/zoom > in.getX() && centerPosition.x - (width/2)/zoom < in.getX()+in.getWidth()*in.getScaleX())
		{
			//Checks y
			if(centerPosition.y + (height/2)/zoom > in.getY() && centerPosition.y - (height/2)/zoom < in.getY()+in.getHeight()*in.getScaleY())
			{
				float relX = (in.getCenterX()-centerPosition.x)*zoom;
				float relY = (in.getCenterY()-centerPosition.y)*zoom;
				in.setScaleX(in.getScaleX()*zoom);
				in.setScaleY(in.getScaleY()*zoom);
				in.setX(realPosition.x + relX + (width/2) - in.getScaleX()*in.getWidth()/2);
				in.setY(realPosition.y + relY + (height/2) - in.getScaleY()*in.getHeight()/2);

				in.draw(tint);
			}
		}
	}
}
void Camera::draw(Image in, DWORD tint, bool hoizontalFlip, bool virticalFlip)
{
	if(in.getVisible())
	{
		//Checks x
		if(centerPosition.x + (width/2)/zoom > in.getX() && centerPosition.x - (width/2)/zoom < in.getX()+in.getWidth()*in.getScale())
		{
			//Checks y
			if(centerPosition.y + (height/2)/zoom > in.getY() && centerPosition.y - (height/2)/zoom < in.getY()+in.getHeight()*in.getScale())
			{
				float relX = (in.getCenterX()-centerPosition.x)*zoom;
				float relY = (in.getCenterY()-centerPosition.y)*zoom;
				in.setScale(in.getScale()*zoom);
				in.setX(realPosition.x + relX + (width/2) - in.getScale()*in.getWidth()/2);
				in.setY(realPosition.y + relY + (height/2) - in.getScale()*in.getHeight()/2);
				in.flipVertical(hoizontalFlip);
				in.flipVertical(virticalFlip);
				in.draw(tint);
			}
		}
	}
}
void Camera::draw(Entity& in)
{
	draw(in, in.color);
}
void Camera::draw(Entity& in, bool hoizontalFlip, bool virticalFlip)
{
	Entity temp = in;
	//temp.flipHorizontal(hoizontalFlip);
	//temp.flipVertical(virticalFlip);
	draw(temp, temp.color, hoizontalFlip, virticalFlip);
}
D3DXVECTOR2 Camera::getRealPos(float xIn, float yIn)
{
	//return D3DXVECTOR2(xIn, yIn);
	float relX = (xIn-(realPosition.x+width/2))/zoom;
	float relY = (yIn-(realPosition.y+height/2))/zoom;
	return D3DXVECTOR2(relX + centerPosition.x, relY + centerPosition.y);
}
D3DXVECTOR2 Camera::getCameraRelitivePos(float xIn, float yIn)
{
	float relX = (xIn-(centerPosition.x))/zoom;
	float relY = (yIn-(centerPosition.y))/zoom;
	return D3DXVECTOR2(relX + centerPosition.x, relY + centerPosition.y);
}