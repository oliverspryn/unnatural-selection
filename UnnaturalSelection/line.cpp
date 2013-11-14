//The implementations for lines and rays
//By Michael Wiegand
// 11/13/2013

#include"line.h"

namespace myLines
{
	Line::Line()
	{
		pos = D3DXVECTOR2(0, 0);
		velocity = D3DXVECTOR2(0, 0);
		angle = 0;
		length = 0;
	}
	Line::Line(D3DXVECTOR2 pos, D3DXVECTOR2 velocity): pos(pos)
	{
		setVelocity(velocity);
	}
	void Line::setPosition(D3DXVECTOR2 in)
	{
		pos = in;
	}
	void Line::setVelocity(D3DXVECTOR2 in)
	{
		velocity = in;
		angle = atan2(velocity.y, velocity.x);
		length = sqrt(velocity.x*velocity.x + velocity.y*velocity.y);
	}
	void Line::setAngle(float in)
	{
		velocity.x = cos(in)*length;
		velocity.y = sin(in)*length;
		angle = in;
		if(-PI > in || in > PI)
		{
			angle = atan2(velocity.y, velocity.x);
		}
	}
	void Line::setSpeed(float in)
	{
		in = abs(in);
		length = in;
		velocity.x = cos(angle)*length;
		velocity.y = sin(angle)*length;
	}

	//Sets the time if line intersects b 
	bool Line::getTimeOfIntersect(Line &b, float &time)
	{
		//If Parellel
		if(angle == b.angle || angle == (-1)*b.angle)
		{
			return false;
		}
		else//when not parellel
		{
			time = D3DXVec2CCW(&D3DXVECTOR2(b.pos-pos), &b.velocity)/D3DXVec2CCW(&velocity, &b.velocity);
			return true;
		}

	}



	Ray::Ray(): Line()
	{
		rayLength = 0;
	}
	Ray::Ray(D3DXVECTOR2 pos, D3DXVECTOR2 velocity, float length): Line(pos, velocity)
	{
		setRayLength(length);
	}
	bool Ray::getTimeOfIntersect(Line &b, float &time)
	{
		float tempTime = time;
		if(Line::getTimeOfIntersect(b, tempTime))
		{
			if(tempTime >= 0)
			{
				D3DXVECTOR2 deltaPos = getPosition(tempTime) - getPosition(0);
				if(deltaPos.x*deltaPos.x + deltaPos.y*deltaPos.y < rayLength*rayLength)
				{
					time = tempTime;
					return true;
				}
			}else{
				return false;
			}

		}else{
			return false;
		}
		return false;
	}
	bool Ray::getTimeOfIntersectRay(Ray &b, float &time)
	{
		float tempTime = time;
		if(getTimeOfIntersect(b, tempTime))
		{
			float t;
			D3DXVECTOR2 intersectPos(getPosition(tempTime));
			D3DXVECTOR2 bPos(b.getPosition(0));
			D3DXVECTOR2 deltaPos(intersectPos - bPos);
			if(b.getVelocity().x != 0)
			{
				t = (intersectPos.x-bPos.x)/b.getVelocity().x;
			}else{
				t = (intersectPos.y-bPos.y)/b.getVelocity().y;
			}

			if(t >= 0)
			if(deltaPos.x*deltaPos.x + deltaPos.y*deltaPos.y < b.rayLength*b.rayLength)
			//if(deltaPos.x*deltaPos.x + deltaPos.y*deltaPos.y < rayLength*rayLength)
			{
				time = tempTime;
				return true;
			}
		}

		return false;
	}
}