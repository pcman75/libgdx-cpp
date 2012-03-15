#pragma once
#include "Timer.h"

class WindowsTimer :
	public Timer
{
public:
	WindowsTimer();

	/** Start the timer**/
	virtual void startTimer();

	/** Returns the nanoseconds passed since the timer was started**/
	virtual long long stopTimer();

	//TODO:
	virtual long long systemNanoSeconds();

private:
	LONGLONG getFrequency();

private:
	LARGE_INTEGER start;
	LARGE_INTEGER stop;
	LONGLONG frequency;
};

