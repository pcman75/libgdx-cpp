#pragma once
#include "applicationlistener.h"
#include "Mesh.h"
#include "Texture.h"

class HelloWorldApp :
	public ApplicationListener
{
private:
	Mesh* m_mesh;
	Texture* m_texture;

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

