#include "stdafx.h"
#include "Sprite.h"
#include "NumberUtils.h"
#include "MathUtils.h"
#include "SpriteBatch.h"

const int Sprite::X1 = 0;
const int Sprite::Y1 = 1;
const int Sprite::C1 = 2;
const int Sprite::U1 = 3;
const int Sprite::V1 = 4;
const int Sprite::X2 = 5;
const int Sprite::Y2 = 6;
const int Sprite::C2 = 7;
const int Sprite::U2 = 8;
const int Sprite::V2 = 9;
const int Sprite::X3 = 10;
const int Sprite::Y3 = 11;
const int Sprite::C3 = 12;
const int Sprite::U3 = 13;
const int Sprite::V3 = 14;
const int Sprite::X4 = 15;
const int Sprite::Y4 = 16;
const int Sprite::C4 = 17;
const int Sprite::U4 = 18;
const int Sprite::V4 = 19;

void Sprite::init()
{
	m_color = Color(1, 1, 1, 1);
	m_x = m_y = m_width = m_height = m_originX = m_originY = m_rotation = 0.f;
	m_scaleX = m_scaleY = 1.f;
	m_dirty = true;
}

void Sprite::init(Texture* texture, int srcX, int srcY, int srcWidth, int srcHeight)
{
	if(texture == NULL) 
		throw new GdxRuntimeException("texture cannot be null.");
	m_texture = texture;
	TextureRegion::setRegion(srcX, srcY, srcWidth, srcHeight);
	setColor(1, 1, 1, 1);
	setSize(abs(srcWidth), abs(srcHeight));
	setOrigin(m_width / 2, m_height / 2);
}


/** Creates an uninitialized sprite. The sprite will need a texture, texture region, bounds, and color set before it can be
* drawn. */
Sprite::Sprite()
{
	init();
}

/** Creates a sprite with width, height, and texture region equal to the size of the texture. */
Sprite::Sprite(Texture* texture)
{
	init();
	init(texture, 0, 0, texture->getWidth(), texture->getHeight());
}

/** Creates a sprite with width, height, and texture region equal to the specified size. The texture region's upper left corner
* will be 0,0. * @param srcWidth The width of the texture region. May be negative to flip the sprite when drawn.
* @param srcHeight The height of the texture region. May be negative to flip the sprite when drawn. */
Sprite::Sprite(Texture* texture, int srcWidth, int srcHeight)
{
	init();
	init(texture, 0, 0, srcWidth, srcHeight);
}

/** Creates a sprite with width, height, and texture region equal to the specified size. * @param srcWidth The width of the
* texture region. May be negative to flip the sprite when drawn.
* @param srcHeight The height of the texture region. May be negative to flip the sprite when drawn. */
Sprite::Sprite(Texture* texture, int srcX, int srcY, int srcWidth, int srcHeight)
{
	init();
	init(texture, srcX, srcY, srcWidth, srcHeight);
}

// Note the region is copied.
Sprite::Sprite(TextureRegion* region)
{
	init();
	TextureRegion::setRegion(region);
	setColor(1, 1, 1, 1);
	setSize(abs(region->getRegionWidth()), abs(region->getRegionHeight()));
	setOrigin(m_width / 2, m_height / 2);
}

/** Creates a sprite with width, height, and texture region equal to the specified size, relative to specified sprite's texture
* region.
* @param srcWidth The width of the texture region. May be negative to flip the sprite when drawn.
* @param srcHeight The height of the texture region. May be negative to flip the sprite when drawn. */
Sprite::Sprite(TextureRegion* region, int srcX, int srcY, int srcWidth, int srcHeight)
{
	init();
	TextureRegion::setRegion(region, srcX, srcY, srcWidth, srcHeight);
	setColor(1, 1, 1, 1);
	setSize(abs(srcWidth), abs(srcHeight));
	setOrigin(m_width / 2, m_height / 2);
}

/** Creates a sprite that is a copy in every way of the specified sprite. */
Sprite::Sprite(const Sprite& sprite)
{
	set(sprite);
}

void Sprite::set(const Sprite& sprite)
{
	memcpy(m_vertices, sprite.m_vertices, SPRITE_SIZE * sizeof(float));

	m_texture = sprite.m_texture;
	m_x = sprite.m_x;
	m_y = sprite.m_y;
	m_width = sprite.m_width;
	m_height = sprite.m_height;
	m_originX = sprite.m_originX;
	m_originY = sprite.m_originY;
	m_rotation = sprite.m_rotation;
	m_scaleX = sprite.m_scaleX;
	m_scaleY = sprite.m_scaleY;
	m_dirty = sprite.m_dirty;
}

/** Sets the position and size of the sprite when drawn, before scaling and rotation are applied. If origin, rotation, or scale
* are changed, it is slightly more efficient to set the bounds after those operations. */
void Sprite::setBounds(float x, float y, float width, float height)
{
	m_x = x;
	m_y = y;
	m_width = width;
	m_height = height;

	if(m_dirty) 
		return;

	float x2 = x + width;
	float y2 = y + height;
	float* vertices = m_vertices;
	vertices[X1] = x;
	vertices[Y1] = y;

	vertices[X2] = x;
	vertices[Y2] = y2;

	vertices[X3] = x2;
	vertices[Y3] = y2;

	vertices[X4] = x2;
	vertices[Y4] = y;

	if(m_rotation != 0 || m_scaleX != 1 || m_scaleY != 1) 
		m_dirty = true;
}

/** Sets the size of the sprite when drawn, before scaling and rotation are applied. If origin, rotation, or scale are changed,
* it is slightly more efficient to set the size after those operations. If both position and size are to be changed, it is
* better to use {@link #setBounds(float, float, float, float)}. */
void Sprite::setSize(float width, float height)
{
	m_width = width;
	m_height = height;

	if(m_dirty) 
		return;

	float x2 = m_x + width;
	float y2 = m_y + height;
	float* vertices = m_vertices;
	vertices[X1] = m_x;
	vertices[Y1] = m_y;

	vertices[X2] = m_x;
	vertices[Y2] = y2;

	vertices[X3] = x2;
	vertices[Y3] = y2;

	vertices[X4] = x2;
	vertices[Y4] = m_y;

	if(m_rotation != 0 || m_scaleX != 1 || m_scaleY != 1) 
		m_dirty = true;
}

/** Sets the position where the sprite will be drawn. If origin, rotation, or scale are changed, it is slightly more efficient
* to set the position after those operations. If both position and size are to be changed, it is better to use
* {@link #setBounds(float, float, float, float)}. */
void Sprite::setPosition(float x, float y)
{
	translate(x - m_x, y - m_y);
}

/** Sets the x position where the sprite will be drawn. If origin, rotation, or scale are changed, it is slightly more efficient
* to set the position after those operations. If both position and size are to be changed, it is better to use
* {@link #setBounds(float, float, float, float)}. */
void Sprite::setX(float x)
{
	translateX(x - m_x);
}

/** Sets the y position where the sprite will be drawn. If origin, rotation, or scale are changed, it is slightly more efficient
* to set the position after those operations. If both position and size are to be changed, it is better to use
* {@link #setBounds(float, float, float, float)}. */
void Sprite::setY(float y)
{
	translateY(y - m_y);
}

/** Sets the x position relative to the current position where the sprite will be drawn. If origin, rotation, or scale are
* changed, it is slightly more efficient to translate after those operations. */
void Sprite::translateX(float xAmount)
{
	m_x += xAmount;

	if(m_dirty) 
		return;

	float* vertices = m_vertices;
	vertices[X1] += xAmount;
	vertices[X2] += xAmount;
	vertices[X3] += xAmount;
	vertices[X4] += xAmount;
}

/** Sets the y position relative to the current position where the sprite will be drawn. If origin, rotation, or scale are
* changed, it is slightly more efficient to translate after those operations. */
void Sprite::translateY(float yAmount)
{
	m_y += yAmount;

	if(m_dirty) 
		return;

	float* vertices = m_vertices;
	vertices[Y1] += yAmount;
	vertices[Y2] += yAmount;
	vertices[Y3] += yAmount;
	vertices[Y4] += yAmount;
}

/** Sets the position relative to the current position where the sprite will be drawn. If origin, rotation, or scale are
* changed, it is slightly more efficient to translate after those operations. */
void Sprite::translate(float xAmount, float yAmount)
{
	m_x += xAmount;
	m_y += yAmount;

	if(m_dirty) 
		return;

	float* vertices = m_vertices;
	vertices[X1] += xAmount;
	vertices[Y1] += yAmount;

	vertices[X2] += xAmount;
	vertices[Y2] += yAmount;

	vertices[X3] += xAmount;
	vertices[Y3] += yAmount;

	vertices[X4] += xAmount;
	vertices[Y4] += yAmount;
}

void Sprite::setColor(Color tint)
{
	float color = tint.toFloatBits();
	float* vertices = m_vertices;
	vertices[C1] = color;
	vertices[C2] = color;
	vertices[C3] = color;
	vertices[C4] = color;
}

void Sprite::setColor(float r, float g, float b, float a)
{
	int intBits = ((int)(255 * a) << 24) | ((int)(255 * b) << 16) | ((int)(255 * g) << 8) | ((int)(255 * r));
	float color = NumberUtils::intToFloatColor(intBits);
	float* vertices = m_vertices;
	vertices[C1] = color;
	vertices[C2] = color;
	vertices[C3] = color;
	vertices[C4] = color;
}

/** Sets the origin in relation to the sprite's position for scaling and rotation. */
void Sprite::setOrigin(float originX, float originY)
{
	m_originX = originX;
	m_originY = originY;
	m_dirty = true;
}

void Sprite::setRotation(float degrees)
{
	m_rotation = degrees;
	m_dirty = true;
}

/** Sets the sprite's rotation relative to the current rotation. */
void Sprite::rotate(float degrees)
{
	m_rotation += degrees;
	m_dirty = true;
}

/** Rotates this sprite 90 degrees in-place by rotating the texture coordinates. This rotation is unaffected by
* {@link #setRotation(float)} and {@link #rotate(float)}. */
void Sprite::rotate90(bool clockwise)
{
	float* vertices = m_vertices;

	if(clockwise)
	{
		float temp = vertices[V1];
		vertices[V1] = vertices[V4];
		vertices[V4] = vertices[V3];
		vertices[V3] = vertices[V2];
		vertices[V2] = temp;

		temp = vertices[U1];
		vertices[U1] = vertices[U4];
		vertices[U4] = vertices[U3];
		vertices[U3] = vertices[U2];
		vertices[U2] = temp;
	}
	else
	{
		float temp = vertices[V1];
		vertices[V1] = vertices[V2];
		vertices[V2] = vertices[V3];
		vertices[V3] = vertices[V4];
		vertices[V4] = temp;

		temp = vertices[U1];
		vertices[U1] = vertices[U2];
		vertices[U2] = vertices[U3];
		vertices[U3] = vertices[U4];
		vertices[U4] = temp;
	}
}

void Sprite::setScale(float scaleXY)
{
	m_scaleX = scaleXY;
	m_scaleY = scaleXY;
	m_dirty = true;
}

void Sprite::setScale(float scaleX, float scaleY)
{
	m_scaleX = scaleX;
	m_scaleY = scaleY;
	m_dirty = true;
}

/** Sets the sprite's scale relative to the current scale. */
void Sprite::scale(float amount)
{
	m_scaleX += amount;
	m_scaleY += amount;
	m_dirty = true;
}

/** Returns the packed vertices, colors, and texture coordinates for this sprite. */
float* Sprite::getVertices()
{
	float* vertices = m_vertices;
	if(m_dirty)
	{
		m_dirty = false;

		float localX = -m_originX;
		float localY = -m_originY;
		float localX2 = localX + m_width;
		float localY2 = localY + m_height;
		float worldOriginX = m_x - localX;
		float worldOriginY = m_y - localY;
		if(m_scaleX != 1 || m_scaleY != 1)
		{
			localX *= m_scaleX;
			localY *= m_scaleY;
			localX2 *= m_scaleX;
			localY2 *= m_scaleY;
		}
		if(m_rotation != 0)
		{
			float cosinus = MathUtils::cosDeg(m_rotation);
			float sinus = MathUtils::sinDeg(m_rotation);
			float localXCos = localX * cosinus;
			float localXSin = localX * sinus;
			float localYCos = localY * cosinus;
			float localYSin = localY * sinus;
			float localX2Cos = localX2 * cosinus;
			float localX2Sin = localX2 * sinus;
			float localY2Cos = localY2 * cosinus;
			float localY2Sin = localY2 * sinus;

			float x1 = localXCos - localYSin + worldOriginX;
			float y1 = localYCos + localXSin + worldOriginY;
			vertices[X1] = x1;
			vertices[Y1] = y1;

			float x2 = localXCos - localY2Sin + worldOriginX;
			float y2 = localY2Cos + localXSin + worldOriginY;
			vertices[X2] = x2;
			vertices[Y2] = y2;

			float x3 = localX2Cos - localY2Sin + worldOriginX;
			float y3 = localY2Cos + localX2Sin + worldOriginY;
			vertices[X3] = x3;
			vertices[Y3] = y3;

			vertices[X4] = x1 + (x3 - x2);
			vertices[Y4] = y3 - (y2 - y1);
		}
		else
		{
			float x1 = localX + worldOriginX;
			float y1 = localY + worldOriginY;
			float x2 = localX2 + worldOriginX;
			float y2 = localY2 + worldOriginY;

			vertices[X1] = x1;
			vertices[Y1] = y1;

			vertices[X2] = x1;
			vertices[Y2] = y2;

			vertices[X3] = x2;
			vertices[Y3] = y2;

			vertices[X4] = x2;
			vertices[Y4] = y1;
		}
	}
	return vertices;
}

/** Returns the bounding axis aligned {@link Rectangle} that bounds this sprite. The rectangles x and y coordinates describe its
* bottom left corner.
*
* @return the bounding Rectangle */
const Rectang& Sprite::getBoundingRectangle()
{
	const float* vertices = getVertices();

	float minx = vertices[X1];
	float miny = vertices[Y1];
	float maxx = vertices[X1];
	float maxy = vertices[Y1];

	minx = minx > vertices[X2] ? vertices[X2] : minx;
	minx = minx > vertices[X3] ? vertices[X3] : minx;
	minx = minx > vertices[X4] ? vertices[X4] : minx;

	maxx = maxx < vertices[X2] ? vertices[X2] : maxx;
	maxx = maxx < vertices[X3] ? vertices[X3] : maxx;
	maxx = maxx < vertices[X4] ? vertices[X4] : maxx;

	miny = miny > vertices[Y2] ? vertices[Y2] : miny;
	miny = miny > vertices[Y3] ? vertices[Y3] : miny;
	miny = miny > vertices[Y4] ? vertices[Y4] : miny;

	maxy = maxy < vertices[Y2] ? vertices[Y2] : maxy;
	maxy = maxy < vertices[Y3] ? vertices[Y3] : maxy;
	maxy = maxy < vertices[Y4] ? vertices[Y4] : maxy;

	m_bounds.x = minx;
	m_bounds.y = miny;
	m_bounds.width = maxx - minx;
	m_bounds.height = maxy - miny;

	return m_bounds;
}

void Sprite::draw(SpriteBatch* spriteBatch)
{
	spriteBatch->draw(m_texture, getVertices(), 0, SPRITE_SIZE);
}

void Sprite::draw(SpriteBatch* spriteBatch, float alphaModulation)
{
	Color& color = getColor();
	float oldAlpha = color.a;
	color.a *= alphaModulation;
	setColor(color);
	draw(spriteBatch);
	color.a = oldAlpha;
	setColor(color);
}


float Sprite::getX()
{
	return m_x;
}

float Sprite::getY()
{
	return m_y;
}

float Sprite::getWidth()
{
	return m_width;
}

float Sprite::getHeight()
{
	return m_height;
}

float Sprite::getOriginX()
{
	return m_originX;
}

float Sprite::getOriginY()
{
	return m_originY;
}

float Sprite::getRotation()
{
	return m_rotation;
}

float Sprite::getScaleX()
{
	return m_scaleX;
}

float Sprite::getScaleY()
{
	return m_scaleY;
}

/** Returns the color of this sprite. Changing the returned color will have no affect, {@link #setColor(Color)} or
* {@link #setColor(float, float, float, float)} must be used. */
Color& Sprite::getColor()
{
	int intBits = NumberUtils::floatToIntColor(m_vertices[C1]);
	Color& color = m_color;
	color.r = (intBits & 0xff) / 255.f;
	color.g = ((intBits >> 8) & 0xff) / 255.f;
	color.b = ((intBits >> 16) & 0xff) / 255.f;
	color.a = ((intBits >> 24) & 0xff) / 255.f;
	return color;
}

void Sprite::setRegion(float u, float v, float u2, float v2)
{
	this->m_u = u;
	this->m_v = v;
	this->m_u2 = u2;
	this->m_v2 = v2;

	float* vertices = m_vertices;
	vertices[U1] = u;
	vertices[V1] = v2;

	vertices[U2] = u;
	vertices[V2] = v;

	vertices[U3] = u2;
	vertices[V3] = v;

	vertices[U4] = u2;
	vertices[V4] = v2;
}

void Sprite::setU(float u)
{
	m_u = u;
	m_vertices[U1] = u;
	m_vertices[U2] = u;
}

void Sprite::setV(float v)
{
	m_v = v;
	m_vertices[V2] = v;
	m_vertices[V3] = v;
}

void Sprite::setU2(float u2)
{
	m_u2 = u2;
	m_vertices[U3] = u2;
	m_vertices[U4] = u2;
}

void Sprite::setV2(float v2)
{
	m_v2 = v2;
	m_vertices[V1] = v2;
	m_vertices[V4] = v2;
}

void Sprite::flip(bool x, bool y)
{
	TextureRegion::flip(x, y);
	float* vertices = m_vertices;
	if(x)
	{
		float temp = vertices[U1];
		vertices[U1] = vertices[U3];
		vertices[U3] = temp;
		temp = vertices[U2];
		vertices[U2] = vertices[U4];
		vertices[U4] = temp;
	}
	if(y)
	{
		float temp = vertices[V1];
		vertices[V1] = vertices[V3];
		vertices[V3] = temp;
		temp = vertices[V2];
		vertices[V2] = vertices[V4];
		vertices[V4] = temp;
	}
}

void Sprite::scroll(float xAmount, float yAmount)
{
	float* vertices = m_vertices;
	if(xAmount != 0)
	{
		//float u = (vertices[U1] + xAmount) % 1;
		float u = (vertices[U1] + xAmount) - (int)(vertices[U1] + xAmount);
		float u2 = u + m_width / m_texture->getWidth();
		this->m_u = u;
		this->m_u2 = u2;
		vertices[U1] = u;
		vertices[U2] = u;
		vertices[U3] = u2;
		vertices[U4] = u2;
	}
	if(yAmount != 0)
	{
		//float v = (vertices[V2] + yAmount) % 1;
		float v = (vertices[V2] + yAmount) - (int)(vertices[V2] + yAmount);
		float v2 = v + m_height / m_texture->getHeight();
		this->m_v = v;
		this->m_v2 = v2;
		vertices[V1] = v2;
		vertices[V2] = v;
		vertices[V3] = v;
		vertices[V4] = v2;
	}
}

