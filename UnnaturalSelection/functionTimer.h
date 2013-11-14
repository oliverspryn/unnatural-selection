//Interface for the FunctionTimer class
//By Michael Wiegand
// 11/5/2013

#ifndef FUNCTIONTIMER_H
#define FUNCTIONTIMER_H
#define WIN32_LEAN_AND_MEAN
#include "game.h"

class FunctionTimer
{
public:
	FunctionTimer(int size): size(size)
	{
		top = 0;
		time = new float[size];
		counts = new int[size];
		updated = new bool[size];
		beginTimer = new LARGE_INTEGER[size];
		endTimer = new LARGE_INTEGER[size];
		message = new std::string[size];
		for(int i(0); i < size; i++)
		{
			time[i] = 0;
			counts[i] = 0;
			updated[i] = false;
			message[i] = "No function";
		}
	}
	~FunctionTimer()
	{
		delete [] time;
		delete [] counts;
		delete [] updated;
		delete [] beginTimer;
		delete [] endTimer;
		delete [] message;
	}
	void Add(std::string info)
	{
		if(top < size)
		{
			message[top] = info;
			top++;
		}
	}
	//updates all the bools so the count adds one
	void nextFrame()
	{
		for(int i(0); i < size; i++)
		{
			updated[i] = false;
		}
	}
	void starting(int index)
	{
		if(!(updated)[index])
		{
			(counts)[index]++;
			(updated)[index] = true;
		}
		QueryPerformanceCounter(&(beginTimer)[index]);
	}
	void ending(int index, LARGE_INTEGER &timerFreq)
	{
		QueryPerformanceCounter(&(endTimer)[index]);
		(time)[index] += (float)((endTimer)[index].QuadPart-(beginTimer)[index].QuadPart)/(float)timerFreq.QuadPart;
	}
	float getAverageTime(int index)
	{
		if(index < size && (counts)[index] > 0)
		{
			return (time)[index]/(counts)[index];
		}
		else
		{
			return 0;
		}
	}
	std::string getName(int index)
	{
		if(index < size)
		{
			return (message)[index];
		}else{
			return "Not In Bounds";
		}
	}
	int getSize()
	{
		return top;
	}
private:
	int size;
	float (*time);
	int (*counts);
	bool (*updated);
	LARGE_INTEGER (*beginTimer);
	LARGE_INTEGER (*endTimer);
	std::string (*message);
	int top;


};



#endif