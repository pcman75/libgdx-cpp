#pragma once
#include "Timer.h"

class GlfwTimer :
	public Timer
{
public:
	GlfwTimer();

	/** Start the timer**/
	virtual void startTimer();

	/** Returns the nanoseconds passed since the timer was started**/
	virtual long long stopTimer();

	virtual long long systemNanoSeconds();

private:
	double m_start;
	double m_end;
};


