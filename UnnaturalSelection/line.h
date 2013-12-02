//The interface for lines and rays
//By Michael Wiegand
// 11/13/2013

#ifndef LINE_H
#define LINE_H
#define WIN32_LEAN_AND_MEAN
#include"entity.h"

namespace myLines
{
	class Line
	{
	public:
		Line();
		Line(D3DXVECTOR2 pos, D3DXVECTOR2 velocity);
		D3DXVECTOR2 getPosition(float time)
		{
			return pos + time*velocity;
		}
		D3DXVECTOR2 getVelocity()
		{
			return velocity;
		}
		float getAngle()
		{
			return angle;
		}
		float getLength()
		{
			return length;
		}
		virtual void setPosition(D3DXVECTOR2 in);
		virtual void setVelocity(D3DXVECTOR2 in);
		virtual void setAngle(float in);
		virtual void setSpeed(float in);
		
		//Sets the time if line intersects b 
		virtual bool getTimeOfIntersect(Line &b, float &time);

	private:
		D3DXVECTOR2 pos;
		D3DXVECTOR2 velocity;
		float angle;
		float length;
	};

	class Ray: public Line
	{
	public:
		Ray();
		Ray(D3DXVECTOR2 pos, D3DXVECTOR2 velocity, float length);
		float getRayLength()
		{
			return rayLength;
		}
		void setRayLength(float in)
		{
			rayLength = abs(in);
		}
		virtual bool getTimeOfIntersect(Line &b, float &time);
		virtual bool getTimeOfIntersectRay(Ray &b, float &time);
		virtual bool getTimeOfIntersectMoveingPoint(D3DXVECTOR2 thisVel, D3DXVECTOR2 point, D3DXVECTOR2 pointVel, float &time);
		//returns this shortest time for any of the points of collision
		virtual bool getTimeOfIntersectMovingRays(D3DXVECTOR2 thisVel, Ray &b, D3DXVECTOR2 velB, float &time);

	private:
		float rayLength;

	};




}
#endif