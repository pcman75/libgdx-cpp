#include "stdafx.h"
#include "TextureRegion.h"

/** Constructs a region with no texture and no coordinates defined. */
TextureRegion::TextureRegion()
{
}

/** Constructs a region the size of the specified texture. */
TextureRegion::TextureRegion(Texture* texture)
{
	if(texture == NULL) 
		throw new GdxRuntimeException("texture cannot be null.");
	m_texture = texture;
	setRegion(0, 0, texture->getWidth(), texture->getHeight());
}

/** @param width The width of the texture region. May be negative to flip the sprite when drawn.
* @param height The height of the texture region. May be negative to flip the sprite when drawn. */
TextureRegion::TextureRegion(Texture* texture, int width, int height)
{
	m_texture = texture;
	setRegion(0, 0, width, height);
}

/** @param width The width of the texture region. May be negative to flip the sprite when drawn.
* @param height The height of the texture region. May be negative to flip the sprite when drawn. */
TextureRegion::TextureRegion(Texture* texture, int x, int y, int width, int height)
{
	m_texture = texture;
	setRegion(x, y, width, height);
}

TextureRegion::TextureRegion(Texture* texture, float u, float v, float u2, float v2)
{
	m_texture = texture;
	setRegion(u, v, u2, v2);
}

/** Constructs a region with the same texture and coordinates of the specified region. */
TextureRegion::TextureRegion(TextureRegion* region)
{
	setRegion(region);
}

/** Constructs a region with the same texture as the specified region and sets the coordinates relative to the specified region.
* @param width The width of the texture region. May be negative to flip the sprite when drawn.
* @param height The height of the texture region. May be negative to flip the sprite when drawn. */
TextureRegion::TextureRegion(TextureRegion* region, int x, int y, int width, int height)
{
	setRegion(region, x, y, width, height);
}

/** Sets the texture and sets the coordinates to the size of the specified texture. */
void TextureRegion::setRegion(Texture* texture)
{
	m_texture = texture;
	setRegion(0, 0, m_texture->getWidth(), m_texture->getHeight());
}

/** @param width The width of the texture region. May be negative to flip the sprite when drawn.
* @param height The height of the texture region. May be negative to flip the sprite when drawn. */
void TextureRegion::setRegion(int x, int y, int width, int height)
{
	float invTexWidth = 1.f / m_texture->getWidth();
	float invTexHeight = 1.f / m_texture->getHeight();
	setRegion(x * invTexWidth, y * invTexHeight, (x + width) * invTexWidth, (y + height) * invTexHeight);
}

void TextureRegion::setRegion(float u, float v, float u2, float v2)
{
	m_u = u;
	m_v = v;
	m_u2 = u2;
	m_v2 = v2;
}

/** Sets the texture and coordinates to the specified region. */
void TextureRegion::setRegion(TextureRegion* region)
{
	m_texture = region->m_texture;
	setRegion(region->m_u, region->m_v, region->m_u2, region->m_v2);
}

/** Sets the texture to that of the specified region and sets the coordinates relative to the specified region. */
void TextureRegion::setRegion(TextureRegion* region, int x, int y, int width, int height)
{
	m_texture = region->m_texture;
	setRegion(region->getRegionX() + x, region->getRegionY() + y, width, height);
}

Texture* TextureRegion::getTexture()
{
	return m_texture;
}

void TextureRegion::setTexture(Texture* texture)
{
	m_texture = texture;
}

float TextureRegion::getU()
{
	return m_u;
}

void TextureRegion::setU(float u)
{
	m_u = u;
}

float TextureRegion::getV()
{
	return m_v;
}

void TextureRegion::setV(float v)
{
	m_v = v;
}

float TextureRegion::getU2()
{
	return m_u2;
}

void TextureRegion::setU2(float u2)
{
	m_u2 = u2;
}

float TextureRegion::getV2()
{
	return m_v2;
}

void TextureRegion::setV2(float v2)
{
	m_v2 = v2;
}

int TextureRegion::getRegionX()
{
	return (int)(m_u * m_texture->getWidth());
}

void TextureRegion::setRegionX(int x)
{
	setU(x / (float)m_texture->getWidth());
}

int TextureRegion::getRegionY()
{
	return (int)(m_v * m_texture->getHeight());
}

void TextureRegion::setRegionY(int y)
{
	setV(y / (float)m_texture->getHeight());
}

/** Returns the region's width. May be negative if the texture region is flipped horizontally. */
int TextureRegion::getRegionWidth()
{
	return round((m_u2 - m_u) * m_texture->getWidth());
}

void TextureRegion::setRegionWidth(int width)
{
	setU2(m_u + width / (float)m_texture->getWidth());
}

/** Returns the region's height. May be negative if the texture region is flipped horizontally. */
int TextureRegion::getRegionHeight()
{
	return round((m_v2 - m_v) * m_texture->getHeight());
}

void TextureRegion::setRegionHeight(int height)
{
	setV2(m_v + height / (float)m_texture->getHeight());
}

void TextureRegion::flip(bool x, bool y)
{
	if(x)
	{
		float temp = m_u;
		m_u = m_u2;
		m_u2 = temp;
	}
	if(y)
	{
		float temp = m_v;
		m_v = m_v2;
		m_v2 = temp;
	}
}

/** Offsets the region relative to the current region. Generally the region's size should be the entire size of the texture in
* the direction(s) it is scrolled.
* @param xAmount The percentage to offset horizontally.
* @param yAmount The percentage to offset vertically. This is done in texture space, so up is negative. */
void TextureRegion::scroll(float xAmount, float yAmount)
{
	if(xAmount != 0)
	{
		float width = (m_u2 - m_u) * m_texture->getWidth();
		//TODO:
		//check this
		//m_u = (m_u + xAmount) % 1;
		m_u = (m_u + xAmount) - (int)(m_u + xAmount);
		m_u2 = m_u + width / m_texture->getWidth();
	}
	if(yAmount != 0)
	{
		float height = (m_v2 - m_v) * m_texture->getHeight();
		//m_v = (m_v + yAmount) % 1;
		m_v = (m_v + yAmount) - (int)(m_v + yAmount);
		m_v2 = m_v + height / m_texture->getHeight();
	}
}

/** Helper function to create tiles out of this TextureRegion starting from the top left corner going to the left and ending at
* the bottom right corner. Only complete tiles will be returned so if the region's width or height are not a multiple of the
* tile width and height not all of the region will be used.
*
* @param tileWidth a tile's width in pixels
* @param tileHeight a tile's height in pixels
* @return a 2D array of TextureRegions indexed by [row][column]. */
TextureRegion** TextureRegion::split(int tileWidth, int tileHeight)
{
	throw GdxRuntimeException("not yet implemented");
	/*
	int x = getRegionX();
	int y = getRegionY();
	int width = getRegionWidth();
	int height = getRegionHeight();

	if(width < 0)
	{
	x = x - width;
	width = -width;
	}

	if(height < 0)
	{
	y = y - height;
	height = -height;
	}

	int rows = height / tileHeight;
	int cols = width / tileWidth;

	int startX = x;
	TextureRegion[][] tiles = new TextureRegion[rows][cols];
	for(int row = 0; row < rows; row++, y += tileHeight)
	{
	x = startX;
	for(int col = 0; col < cols; col++, x += tileWidth)
	{
	tiles[row][col] = new TextureRegion(texture, x, y, tileWidth, tileHeight);
	}
	}

	return tiles;
	*/
}

/** Helper function to create tiles out of the given {@link Texture} starting from the top left corner going to the left and
* ending at the bottom right corner. Only complete tiles will be returned so if the texture's width or height are not a
* multiple of the tile width and height not all of the texture will be used.
*
* @param texture the Texture
* @param tileWidth a tile's width in pixels
* @param tileHeight a tile's height in pixels
* @return a 2D array of TextureRegions indexed by [row][column]. */
TextureRegion** TextureRegion::split(Texture* texture, int tileWidth, int tileHeight)
{
	TextureRegion region = new TextureRegion(texture);
	return region.split(tileWidth, tileHeight);
}

inline float TextureRegion::round(float value)
{
	return floor(value + 0.5f);
}

