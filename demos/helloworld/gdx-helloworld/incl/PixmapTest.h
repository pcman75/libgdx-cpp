#pragma once
#include "applicationlistener.h"
#include "Pixmap.h"
#include "Texture.h"
#include "SpriteBatch.h"
#include "TextureRegion.h"

class PixmapTest :
	public ApplicationListener
{
private:
	Pixmap* m_pixmap;
	Texture* m_texture;
	SpriteBatch* m_batch;
	TextureRegion* m_region;

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

