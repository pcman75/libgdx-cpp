//
//  IOSTimer.cpp
//  gdx-ios
//
//  Created by Tamas Jano on 27/03/2012.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "IOSTimer.h"
#include <sys/time.h>
#include <mach/mach_time.h>

IOSTimer::IOSTimer(void)
{
}

long long IOSTimer::systemNanoSeconds()
{
    static mach_timebase_info_data_t info;
    mach_timebase_info(&info);
    uint64_t now = mach_absolute_time();	
    //    now *= info.numer;
    //    now /= info.denom;
    return now;
}

void IOSTimer::startTimer()
{
	m_start = systemNanoSeconds();
}

long long IOSTimer::stopTimer()
{
	double now = systemNanoSeconds();
	return (long long)10E9 * (now - m_start);
}