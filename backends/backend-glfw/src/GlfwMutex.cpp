#include "stdafx.h"
#include "GlfwMutex.h"


GlfwMutex::GlfwMutex()
{
	m_mutex = ::glfwCreateMutex();
}

/*
* This function destroys a mutex object. 
* After a mutex object has been destroyed, it may no longer be used by any thread.
*/
void GlfwMutex::destroy()
{
	::glfwDestroyMutex(m_mutex);
}

/* This function will acquire a lock on the selected mutex object. 
* If the mutex is already locked by another thread, 
* the function will block the calling thread until it is released by the locking thread. 
* Once the function returns, the calling thread has an exclusive lock on the mutex. 
* To release the mutex, call "unlock".
*/
void GlfwMutex::lock()
{
	::glfwLockMutex(m_mutex);
}

/* This function releases the lock of a locked mutex object.*/
void GlfwMutex::unlock()
{
	::glfwUnlockMutex(m_mutex);
}
