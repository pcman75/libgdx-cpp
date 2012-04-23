#include "StdAfx.h"
#include "GlfwTimer.h"
#include "GdxRuntimeException.h"

GlfwTimer::GlfwTimer(void)
{
}

long long GlfwTimer::systemNanoSeconds()
{
	return  (long long)((long long)10E9 * ::glfwGetTime());
}


void GlfwTimer::startTimer()
{
	m_start = ::glfwGetTime();
}

long long GlfwTimer::stopTimer()
{
	double now = ::glfwGetTime();
	return (long long)((long long)10E9 * (now - m_start));
}