#include "stdafx.h"
#include "Gdx2DPixmap.h"
#include "gdx2d.h"
#include "GdxRuntimeException.h"
#include "Gdx.h"

void Gdx2DPixmap::init()
{
	m_pixmap = NULL;
	setBlend(GDX2D_BLEND_SRC_OVER);
	setScale(GDX2D_SCALE_LINEAR);
}

Gdx2DPixmap::Gdx2DPixmap()
{
	init();
}

Gdx2DPixmap::Gdx2DPixmap(const unsigned char* encodedData, int len, int requestedFormat)
{
	createFrom(encodedData, len, requestedFormat);
}

void Gdx2DPixmap::createFrom(const unsigned char* encodedData, int len, int requestedFormat)
{
	init();
	m_pixmap = gdx2d_load(encodedData, len, requestedFormat); 
	if (!m_pixmap) 
		throw new GdxRuntimeException("couldn't load pixmap");
}
/*
Gdx2DPixmap (InputStream in, int requestedFormat)
{
ByteArrayOutputStream bytes = new ByteArrayOutputStream(1024);
byte[] buffer = new byte[1024];
int readBytes = 0;

while ((readBytes = in.read(buffer)) != -1)
{
bytes.write(buffer, 0, readBytes);
}

buffer = bytes.toByteArray();
pixelPtr = load(nativeData, buffer, 0, buffer.length, requestedFormat);
if (pixelPtr == null) throw new IOException("couldn't load pixmap");

basePtr = nativeData[0];
width = (int)nativeData[1];
height = (int)nativeData[2];
format = (int)nativeData[3];
}
*/
Gdx2DPixmap::Gdx2DPixmap(int width, int height, int format)
{
	init();
	m_pixmap = gdx2d_new(width, height, format);
	if (!m_pixmap) 
		throw new GdxRuntimeException("couldn't load pixmap");
}

void Gdx2DPixmap::dispose()
{
	gdx2d_free(m_pixmap);
}

void Gdx2DPixmap::clear(int color)
{
	gdx2d_clear(m_pixmap, color);
}

void Gdx2DPixmap::setPixel(int x, int y, int color)
{
	gdx2d_set_pixel(m_pixmap, x, y, color);
}

int Gdx2DPixmap::getPixel (int x, int y)
{
	return gdx2d_get_pixel(m_pixmap, x, y);
}

void Gdx2DPixmap::drawLine (int x, int y, int x2, int y2, int color)
{
	gdx2d_draw_line(m_pixmap, x, y, x2, y2, color);
}

void Gdx2DPixmap::drawRect (int x, int y, int width, int height, int color)
{
	gdx2d_draw_rect(m_pixmap, x, y, width, height, color);
}

void Gdx2DPixmap::drawCircle (int x, int y, int radius, int color)
{
	gdx2d_draw_circle(m_pixmap, x, y, radius, color);
}

void Gdx2DPixmap::fillRect (int x, int y, int width, int height, int color)
{
	gdx2d_fill_rect(m_pixmap, x, y, width, height, color);
}

void Gdx2DPixmap::fillCircle (int x, int y, int radius, int color)
{
	gdx2d_fill_circle(m_pixmap, x, y, radius, color);
}

void Gdx2DPixmap::drawPixmap(Gdx2DPixmap* src, int srcX, int srcY, int dstX, int dstY, int width, int height)
{
	gdx2d_draw_pixmap(src->m_pixmap, m_pixmap, srcX, srcY, width, height, dstX, dstY, width, height);
}

void Gdx2DPixmap::drawPixmap (Gdx2DPixmap* src, int srcX, int srcY, int srcWidth, int srcHeight, int dstX, int dstY, int dstWidth,
	int dstHeight)
{
	gdx2d_draw_pixmap(src->m_pixmap, m_pixmap, srcX, srcY, srcWidth, srcHeight, dstX, dstY, dstWidth, dstHeight);
}

/*
Gdx2DPixmap newPixmap (InputStream in, int requestedFormat)
{
try
{
return new Gdx2DPixmap(in, requestedFormat);
}
catch (IOException e)
{
return null;
}
}
*/

Gdx2DPixmap* Gdx2DPixmap::newPixmap (int width, int height, int format)
{
	return new Gdx2DPixmap(width, height, format);
}

unsigned char* Gdx2DPixmap::getPixels ()
{
	return m_pixmap->pixels;
}

int Gdx2DPixmap::getHeight ()
{
	return  m_pixmap->height;
}

int Gdx2DPixmap::getWidth ()
{
	return  m_pixmap->width;
}

int Gdx2DPixmap::getFormat () const
{
	return  m_pixmap->format;
}

int Gdx2DPixmap::getGLInternalFormat ()
{
	switch( m_pixmap->format)
	{
	case GDX2D_FORMAT_ALPHA:
		return GL_ALPHA;
	case GDX2D_FORMAT_LUMINANCE_ALPHA:
		return GL_LUMINANCE_ALPHA;
	case GDX2D_FORMAT_RGB888:
	case GDX2D_FORMAT_RGB565:
		return GL_RGB;
	case GDX2D_FORMAT_RGBA8888:
	case GDX2D_FORMAT_RGBA4444:
		return GL_RGBA;
	default:
		throw new GdxRuntimeException("unknown format: " + m_pixmap->format);
	}
}

int Gdx2DPixmap::getGLFormat ()
{
	return getGLInternalFormat();
}

int Gdx2DPixmap::getGLType ()
{
	switch (m_pixmap->format)
	{
	case GDX2D_FORMAT_ALPHA:
	case GDX2D_FORMAT_LUMINANCE_ALPHA:
	case GDX2D_FORMAT_RGB888:
	case GDX2D_FORMAT_RGBA8888:
		return GL_UNSIGNED_BYTE;
	case GDX2D_FORMAT_RGB565:
		return GL_UNSIGNED_SHORT_5_6_5;
	case GDX2D_FORMAT_RGBA4444:
		return GL_UNSIGNED_SHORT_4_4_4_4;
	default:
		throw new GdxRuntimeException("unknown format: " + m_pixmap->format);
	}
}

std::string Gdx2DPixmap::getFormatString ()
{
	switch(m_pixmap->format)
	{
	case GDX2D_FORMAT_ALPHA:
		return "alpha";
	case GDX2D_FORMAT_LUMINANCE_ALPHA:
		return "luminance alpha";
	case GDX2D_FORMAT_RGB888:
		return "rgb888";
	case GDX2D_FORMAT_RGBA8888:
		return "rgba8888";
	case GDX2D_FORMAT_RGB565:
		return "rgb565";
	case GDX2D_FORMAT_RGBA4444:
		return "rgba4444";
	default:
		return "unknown";
	}
}

void Gdx2DPixmap::setBlend (int blend)
{
	gdx2d_set_blend(blend);
}

void Gdx2DPixmap::setScale (int scale)
{
	gdx2d_set_scale(scale);
}

