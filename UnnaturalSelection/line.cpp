//The implementations for lines and rays
//By Michael Wiegand
// 11/13/2013

#include"line.h"

namespace myLines
{
	int sign(float in)
	{
		if(in < 0)
		{
			return -1;
		}else if(0 < in){
			return 1;
		}else{
			return 0;
		}
	}
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
		velocity = in*velocity/length;
		length = in;

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
	bool Ray::getTimeOfIntersectMoveingPoint(D3DXVECTOR2 thisVel, D3DXVECTOR2 point, D3DXVECTOR2 pointVel, float &time)
	{
		//times each end of the vectors hit
		float t1(0);
		//weather the ray hits at the time
		bool v1(false);
		
		if(thisVel == pointVel  || pointVel == D3DXVECTOR2(0,0))
		{
			return false;
		}else{
			//this start pos
			t1 = D3DXVec2CCW(&D3DXVECTOR2(getPosition(0)-point), &getVelocity())/D3DXVec2CCW(&D3DXVECTOR2(pointVel-thisVel), &getVelocity());
		}
		//Collision points on ray
		D3DXVECTOR2 c1 = point + pointVel*t1-(getPosition(0) + thisVel*t1);
		v1 = (t1 >= 0 && c1.x*c1.x + c1.y*c1.y <= rayLength*rayLength && sign(c1.x) == sign(getVelocity().x) && sign(c1.y) == sign(getVelocity().y));
		if(v1)
		{
			time = t1;
			return true;
		}
		return false;
	}

	bool Ray::getTimeOfIntersectMovingRays(D3DXVECTOR2 thisVel, Ray &b, D3DXVECTOR2 velB, float &time)
	{
		//times each end of the vectors hit
		float tempTime(0), hitTime(0);
		bool hit(false);
		float thisEndTime(rayLength/getLength()), bEndTime(b.getRayLength()/b.getLength());
		//this start pos
		if(getTimeOfIntersectMoveingPoint(thisVel, b.getPosition(0), velB, tempTime))
		{
			if(hit)
			{
				if(tempTime < hitTime)
				{
					hitTime = tempTime;
				}
			}else{
				hit = true;
				hitTime = tempTime;
			}
		}
		//this end pos
		if(getTimeOfIntersectMoveingPoint(thisVel, b.getPosition(bEndTime), velB, tempTime))
		{
			if(hit)
			{
				if(tempTime < hitTime)
				{
					hitTime = tempTime;
				}
			}else{
				hit = true;
				hitTime = tempTime;
			}
		}
		//Line b start pos
		if(b.getTimeOfIntersectMoveingPoint(velB, getPosition(0), thisVel, tempTime))
		{
			if(hit)
			{
				if(tempTime < hitTime)
				{
					hitTime = tempTime;
				}
			}else{
				hit = true;
				hitTime = tempTime;
			}
		}
		//Line b end pos
		if(b.getTimeOfIntersectMoveingPoint(velB, getPosition(thisEndTime), thisVel, tempTime))
		{
			if(hit)
			{
				if(tempTime < hitTime)
				{
					hitTime = tempTime;
				}
			}else{
				hit = true;
				hitTime = tempTime;
			}
		}
		if(hit)
		{
			time = hitTime;
			return true;
		}
		return false;
	}
}