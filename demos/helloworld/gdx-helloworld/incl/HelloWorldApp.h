#pragma once
#include "applicationlistener.h"

class HelloWorldApp :
	public ApplicationListener
{
public:
	HelloWorldApp(void);
	virtual ~HelloWorldApp(void);

	virtual void create ();
	virtual void resize (int width, int height);
	virtual void render ();
	virtual void pause ();
	virtual void resume ();
	virtual void dispose ();
};

