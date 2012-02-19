#pragma once
#include "GdxTest.h"
#include "Pixmap.h"
#include "Texture.h"
#include "SpriteBatch.h"
#include "TextureRegion.h"

class PixmapTest :
	public GdxTest
{
public:
	PixmapTest();
	virtual ~PixmapTest();

	GDX_DEFINE_CREATOR(PixmapTest);
	
	virtual void create();
	virtual void render();
private:
	Pixmap* m_pixmap;
	Texture* m_texture;
	SpriteBatch* m_batch;
	TextureRegion* m_region;

	virtual bool needsGL20();
};

