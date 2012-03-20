#pragma once

#include "Mutex.h"

/*
* Mutexes are used to securely share data between threads. 
* A mutex object can only be owned by one thread at a time. 
* If more than one thread requires access to a mutex object, 
* all but one thread will be put to sleep until they get access to it.
*/
class GlfwMutex :
	public Mutex
{
	friend class GlfwWaitCondition;
private:
	GLFWmutex m_mutex;

public:

	GlfwMutex();

	/*
	* This function destroys a mutex object. 
	* After a mutex object has been destroyed, it may no longer be used by any thread.
	*/
	virtual void destroy();

	/* This function will acquire a lock on the selected mutex object. 
	* If the mutex is already locked by another thread, 
	* the function will block the calling thread until it is released by the locking thread. 
	* Once the function returns, the calling thread has an exclusive lock on the mutex. 
	* To release the mutex, call "unlock".
	*/
	virtual void lock();

	/* This function releases the lock of a locked mutex object.*/
	virtual void unlock();
};