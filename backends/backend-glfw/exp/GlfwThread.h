#pragma once

#include "Thread.h"

class GlfwThread :
	public Thread
{
private:
	GLFWthread m_thread;

public:
	GlfwThread(ThreadFunc fun, void* arg);
	virtual ~GlfwThread() {}

	/* If waitmode is Wait, the function waits for a thread to die. If waitmode is NoWait,
	* the function checks if a thread exists and returns immediately.
	*
	* @return
	* The function returns true if the specified thread died after the function was called, or the thread
	* did not exist, in which case "wait" will return immediately regardless of waitmode. 
	* The function returns false if waitmode is NoWait, and the specified thread exists and is still
	* running
	*/
	virtual bool wait(WaitMode mode);


	/*
	* This function kills a running thread and removes it from the thread list.
	*
	* Notes: This function is a very dangerous operation, which may interrupt a thread in the middle of an important
	* operation, and its use is discouraged. You should always try to end a thread in a graceful way using
	* thread communication, and use wait() in order to wait for the thread to die.
	*/
	virtual void destroy();
};