#include "stdafx.h"
#include "GlfwThreading.h"
#include "GlfwThread.h"
#include "GlfwMutex.h"
#include "GlfwWaitCondition.h"

/*
* This function creates a new thread, which executes within the same address space as the calling process.
* The thread entry point is specified with the "function" argument.
* Once the thread function returns, the thread dies.
* Notes:
* Even if the function returns a Thread, indicating that the thread was created successfully, the
* thread may be unable to execute, for instance if the thread start address is not a valid thread entry point.*/
Thread* GlfwThreading::createThread(ThreadFunc fun, void* arg)
{
	return new GlfwThread(fun, arg);
}

/*
* The function returns a mutex, or NULL if the mutex could not be created.
* This function creates a mutex object, which can be used to control access to data that is shared between threads.
*/
Mutex* GlfwThreading::createMutex()
{
	return new GlfwMutex();
}

/*
* This function creates a condition variable object, which can be used to synchronize threads.
*/
WaitCondition* GlfwThreading::createWaitCondition()
{
	return new GlfwWaitCondition();
}