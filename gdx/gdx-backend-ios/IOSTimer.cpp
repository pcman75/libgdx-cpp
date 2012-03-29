//
//  IOSTimer.cpp
//  gdx-ios
//
//  Created by Tamas Jano on 27/03/2012.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "IOSTimer.h"
#include <sys/time.h>

IOSTimer::IOSTimer(void)
{
}

long long IOSTimer::systemNanoSeconds()
{
    timeval time;
    gettimeofday(&time, NULL);
	return  (long long)1000 * time.tv_usec;
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