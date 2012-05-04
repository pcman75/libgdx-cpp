//
//  IOSTimer.h
//  gdx-ios
//
//  Created by Tamas Jano on 27/03/2012.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef gdx_ios_IOSTimer_h
#define gdx_ios_IOSTimer_h

#include "Timer.h"
#include <sys/time.h>
#include <mach/mach_time.h>

class IOSTimer : public Timer
{
public:
    IOSTimer(void);
    
    /** Start the timer**/
	virtual void startTimer();
    
	/** Returns the nanoseconds passed since the timer was started**/
	virtual long long stopTimer();
    
	virtual long long systemNanoSeconds();
private:
	double m_start;
	double m_end;
    mach_timebase_info_data_t m_timeInfo;
};

#endif
