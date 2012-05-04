//
//  IOSTimer.cpp
//  gdx-ios
//
//  Created by Tamas Jano on 27/03/2012.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "IOSTimer.h"

IOSTimer::IOSTimer(void)
{
    mach_timebase_info(&m_timeInfo);
}

long long IOSTimer::systemNanoSeconds()
{
    uint64_t now = mach_absolute_time();	
    now = now * m_timeInfo.numer / m_timeInfo.denom;
    return now;
}

void IOSTimer::startTimer()
{
	m_start = systemNanoSeconds();
}

long long IOSTimer::stopTimer()
{
	long long now = systemNanoSeconds();
	return now - m_start;
}