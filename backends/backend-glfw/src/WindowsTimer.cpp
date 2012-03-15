#include "StdAfx.h"
#include "WindowsTimer.h"
#include "GdxRuntimeException.h"

long long WindowsTimer::systemNanoSeconds()
{
	LARGE_INTEGER systemCounter;
	DWORD_PTR oldmask = ::SetThreadAffinityMask(::GetCurrentThread(), 0);
	::QueryPerformanceCounter(&systemCounter);
	::SetThreadAffinityMask(::GetCurrentThread(), oldmask);

	return  (long long)(10E9 * systemCounter.QuadPart / frequency);
}

WindowsTimer::WindowsTimer(void)
{
	frequency = getFrequency();
}

LONGLONG WindowsTimer::getFrequency(void)
{
	LARGE_INTEGER proc_freq;
	if (!::QueryPerformanceFrequency(&proc_freq)) 
		throw GdxRuntimeException("QueryPerformanceFrequency() failed");

	return proc_freq.QuadPart;
}

void WindowsTimer::startTimer()
{
	DWORD_PTR oldmask = ::SetThreadAffinityMask(::GetCurrentThread(), 0);
	::QueryPerformanceCounter(&start);
	::SetThreadAffinityMask(::GetCurrentThread(), oldmask);
}

long long WindowsTimer::stopTimer()
{
	DWORD_PTR oldmask = ::SetThreadAffinityMask(::GetCurrentThread(), 0);
	::QueryPerformanceCounter(&stop);
	::SetThreadAffinityMask(::GetCurrentThread(), oldmask);

	return (long long)(((stop.QuadPart - start.QuadPart) / frequency) * 10E6);
}