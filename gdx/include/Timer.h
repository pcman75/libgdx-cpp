#pragma once

/** A Timer interface. 
 * The highest resolution timer available is used to implemented it for each
 * platform: Windows use QueryPerformanceCounter. Unix use clock_gettime() ???
 */
class Timer 
{
public:
	/** Start the timer**/
	virtual void startTimer() = 0;

	/** Returns the nanoseconds passed since the timer was started**/
	virtual long long stopTimer() = 0;

	virtual long long systemNanoSeconds() = 0;
};