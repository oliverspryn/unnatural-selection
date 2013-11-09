//This is the implementation of camera
//By Michael Wiegand 
// 11/8/2013
#include "camera.h"

Camera::Camera(int width, int height, int xReal, int yReal, int x, int y, float zoom): width(width), height(height), realPosition(xReal, yReal), centerPosition(x+width/2, y+height/2), zoom(zoom)
{
	
}
void Camera::draw(Image in)
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

				in.draw();
			}
		}
	}
}