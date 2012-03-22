#pragma once

#include "WaitCondition.h"

/*
Condition variables are used to synchronize threads. A thread can wait for a condition variable to be
signaled by another thread.
*/
class GlfwWaitCondition :
	public WaitCondition
{
private:
	GLFWcond m_cond;

public:
	GlfwWaitCondition();
	virtual ~GlfwWaitCondition();

	/*
	* This function atomically unlocks the mutex specified by mutex, and waits for the condition variable
	* cond to be signaled. The thread execution is suspended and does not consume any CPU time until the
	* condition variable is signaled or the amount of time specified by timeout has passed. If timeout is
	* "infinity", "wait" will wait forever for cond to be signaled. 
	* Before returning to thecalling thread, wait automatically re-acquires the mutex.
	* @param timeout
	* Maximum time to wait for the condition variable. The parameter can either be a positive time (in nanoseconds), 
	* or "infinity".
	* Notes
	* The mutex specified by mutex must be locked by the calling thread before entrance to wait.
	* A condition variable must always
	*/
	virtual void wait(Mutex* mutex, long long timeout);


	/*
	* This function restarts one of the threads that are waiting on the condition variable cond. If no threads
	* are waiting on cond, nothing happens. If several threads are waiting on cond, exactly one is restarted,
	* but it is not specified which.
	* Notes
	* When several threads are waiting for the condition variable, which thread is started depends on
	* operating system scheduling rules, and may vary from system to system and from time to time.
	*/
	virtual void signal();

	/*
	* This function restarts all the threads that are waiting on the condition variable cond. If no threads are
	* waiting on cond, nothing happens.
	* Notes
	* When several threads are waiting for the condition variable, the order in which threads are started
	* depends on operating system scheduling rules, and may vary from system to system and from time to
	* time.
	*/
	virtual void broadcast();
};