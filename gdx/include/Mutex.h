#pragma once

/*
* Mutexes are used to securely share data between threads. 
* A mutex object can only be owned by one thread at a time. 
* If more than one thread requires access to a mutex object, 
* all but one thread will be put to sleep until they get access to it.
*/
class Mutex
{
public:
	virtual ~Mutex() {}

	/* This function will acquire a lock on the selected mutex object. 
	* If the mutex is already locked by another thread, 
	* the function will block the calling thread until it is released by the locking thread. 
	* Once the function returns, the calling thread has an exclusive lock on the mutex. 
	* To release the mutex, call "unlock".
	*/
	virtual void lock() = 0;

	/* This function releases the lock of a locked mutex object.*/
	virtual void unlock() = 0;
};