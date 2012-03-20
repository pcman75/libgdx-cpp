#pragma once

#include "Threading.h"

/*
* A thread is a separate execution path within a process. All threads within a process share the same
* address space and resources. Threads execute in parallel, either virtually by means of time-sharing on a
* single processor, or truly in parallel on multiple processors. Even on a multi-processor system,
* time-sharing is employed in order to maximize processor utilization and to ensure fair scheduling.
* libgdx-cpp provides an operating system independent interface to thread management.
*/
class GlfwThreading : 
	public Threading
{
public:
	/*
	* This function creates a new thread, which executes within the same address space as the calling process.
	* The thread entry point is specified with the "function" argument.
	* Once the thread function returns, the thread dies.
	* Notes:
	* Even if the function returns a Thread, indicating that the thread was created successfully, the
	* thread may be unable to execute, for instance if the thread start address is not a valid thread entry point.*/
	virtual Thread* createThread(ThreadFunc fun, void* arg);

	/*
	* The function returns a mutex, or NULL if the mutex could not be created.
	* This function creates a mutex object, which can be used to control access to data that is shared between threads.
	*/
	virtual Mutex* createMutex();

	/*
	* This function creates a condition variable object, which can be used to synchronize threads.
	*/
	virtual WaitCondition* createWaitCondition();
};