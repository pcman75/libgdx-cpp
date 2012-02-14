#include "StdAfx.h"
#include "PixmapTest.h"
#include "PixmapIO.h"

PixmapTest::PixmapTest()
{
}


PixmapTest::~PixmapTest()
{	
}

void PixmapTest::create ()
{
	m_pixmap = new Pixmap(2, 2, Pixmap::Format::RGBA8888);
	m_pixmap->setColor(1, 0, 0, 1);
	m_pixmap->fill();
	
	//PixmapIO.writePNG(Gdx.files.absolute("test.png"), pixmap);
	//TODO:
	FileHandle handle( "c:\\test.png");
	PixmapIO::writePNG(handle, m_pixmap);

	m_pixmap->dispose();
	delete m_pixmap;
		
	// Create an empty dynamic pixmap
	m_pixmap = new Pixmap(800, 480, Pixmap::Format::RGBA8888); // Pixmap.Format.RGBA8888);

	// Create a texture to contain the pixmap
	m_texture = new Texture(1024, 1024, Pixmap::Format::RGBA8888); // Pixmap.Format.RGBA8888);
	m_texture->setFilter(Texture::TextureFilter::Nearest, Texture::TextureFilter::Linear);
	m_texture->setWrap(Texture::TextureWrap::ClampToEdge, Texture::TextureWrap::ClampToEdge);

	m_pixmap->setColor(1.0f, 0.0f, 0.0f, 1.0f); // Red
	m_pixmap->drawLine(0, 0, 100, 100);

	m_pixmap->setColor(0.0f, 0.0f, 1.0f, 1.0f); // Blue
	m_pixmap->drawLine(100, 100, 200, 0);

	m_pixmap->setColor(0.0f, 1.0f, 0.0f, 1.0f); // Green
	m_pixmap->drawLine(100, 0, 100, 100);

	m_pixmap->setColor(1.0f, 1.0f, 1.0f, 1.0f); // White
	m_pixmap->drawCircle(400, 300, 100);

	FileHandle handle2( "c:\\test2.png");
	PixmapIO::writePNG(handle2, m_pixmap);

	// Blit the composited overlay to a texture
	m_texture->draw(m_pixmap, 0, 0);
	m_region = new TextureRegion(m_texture, 0, 0, 800, 480);
	m_batch = new SpriteBatch();

	Pixmap* pixmap = new Pixmap(512, 1024, Pixmap::Format::RGBA8888);
	for (int y = 0; y < pixmap->getHeight(); y++) 
	{ 
		// 1024
		for (int x = 0; x < pixmap->getWidth(); x++) 
		{ 
			// 512
			pixmap->getPixel(x, y);
		}
	}
	pixmap->dispose();
	delete pixmap;
}

void PixmapTest::resize (int width, int height)
{
}

void PixmapTest::render ()
{
		Gdx.gl->glClearColor(0.6f, 0.6f, 0.6f, 1);
		Gdx.gl->glClear(GL10::GDX_GL_COLOR_BUFFER_BIT);
		m_batch->begin();
		m_batch->draw(m_region, 0, 0);
		m_batch->end();
}

void PixmapTest::pause (){}

void PixmapTest::resume (){}

void PixmapTest::dispose ()
{
}
