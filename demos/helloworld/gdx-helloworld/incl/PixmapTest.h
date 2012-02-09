#pragma once
#include "applicationlistener.h"
#include "Pixmap.h"
#include "Texture.h"
//#include "SpriteBatch.h"
//#include "TextureRegion.h"

class PixmapTest :
	public ApplicationListener
{
private:
	Pixmap pixmap;
	Texture texture;
	//SpriteBatch batch;
	//TextureRegion region;

public:
	PixmapTest(void);
	virtual ~PixmapTest(void);

	virtual void create ();
	virtual void resize (int width, int height);
	virtual void render ();
	virtual void pause ();
	virtual void resume ();
	virtual void dispose ();
};

