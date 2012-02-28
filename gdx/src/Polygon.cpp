#include "stdafx.h"
#include "Polygon.h"
#include "GdxRuntimeException.h"
#include "MathUtils.h"

Polygon::Polygon()
{
  m_scaleX = m_scaleY = 1;
}

Polygon::Polygon( const std::vector<float>& vertices)
{
  m_scaleX = m_scaleY = 1;

  if( vertices.size() < 6) throw new GdxRuntimeException("polygons must contain at least 3 points.");
	m_vertices = vertices;
}

std::vector<float> Polygon::getVertices() 
{
	if( !m_dirty) return m_vertices;

	std::vector<float> retVertices = m_vertices;
	int numFloats = retVertices.size();

	float translateX = m_x + m_originX;
	float translateY = m_y + m_originY;
	float fcos = MathUtils::cosDeg( m_rotation);
	float fsin = MathUtils::sinDeg( m_rotation);
	float x, y;
	for( int i = 0; i < numFloats; i += 2) 
  {
		x = m_vertices[i];
		y = m_vertices[i + 1];

		// move vertices to local coordinates
		x -= translateX;
		y -= translateY;

		// scale if needed
		if( m_scaleX != 1 || m_scaleY != 1) 
    {
			x *= m_scaleX;
			y *= m_scaleY;
		}

		// rotate if needed
		if( m_rotation != 0) 
    {
			float oldX = x;
			x = fcos * x - fsin * y;
			y = fsin * oldX + fcos * y;
		}

		// move vertices back to world coordinates
		x += translateX;
		y += translateY;

		retVertices[i] = x;
		retVertices[i + 1] = y;
	}

  //m_dirty = false;

	return retVertices;
}


void Polygon::setOrigin( float originX, float originY) 
{
	m_originX = originX;
	m_originY = originY;
	m_dirty = true;
}

void Polygon::setPosition( float x, float y) 
{
	m_x = x;
	m_y = y;
	m_dirty = true;
}

void Polygon::translate( float x, float y) 
{
	m_x += x;
	m_y += y;
	m_dirty = true;
}

void Polygon::setRotation( float degrees) 
{
	m_rotation = degrees;
	m_dirty = true;
}

void Polygon::rotate( float degrees) 
{
	m_rotation += degrees;
	m_dirty = true;
}

void Polygon::setScale( float scaleX, float scaleY) 
{
	m_scaleX = scaleX;
	m_scaleY = scaleY;
	m_dirty = true;
}

void Polygon::scale( float amount) 
{
	m_scaleX += amount;
	m_scaleY += amount;
	m_dirty = true;
}

float Polygon::area () 
{
	float area = 0;

	std::vector<float> vertices = getVertices();
	int numFloats = vertices.size();

	int x1, y1, x2, y2;
	for (int i = 0; i < numFloats; i += 2) 
  {
		x1 = i;
		y1 = i + 1;
		x2 = (i + 2) % numFloats;
		y2 = (i + 3) % numFloats;

		area += vertices[x1] * vertices[y2];
		area -= vertices[x2] * vertices[y1];
	}
	area *= 0.5f;
	return area;
}

Rectang Polygon::getBoundingRectangle() 
{
	std::vector<float> vertices = getVertices();

	float minX = vertices[0];
	float minY = vertices[1];
	float maxX = vertices[0];
	float maxY = vertices[1];

	int numFloats = vertices.size();
	for (int i = 2; i < numFloats; i += 2) 
  {
		minX = minX > vertices[i] ? vertices[i] : minX;
		minY = minY > vertices[i + 1] ? vertices[i + 1] : minY;
		maxX = maxX < vertices[i] ? vertices[i] : maxX;
		maxY = maxY < vertices[i + 1] ? vertices[i + 1] : maxY;
	}

	m_bounds.x = minX;
	m_bounds.y = minY;
	m_bounds.width = maxX - minX;
	m_bounds.height = maxY - minY;

	return m_bounds;
}

bool Polygon::contains( float x, float y) 
{
	std::vector<float> vertices = getVertices();
	int numFloats = vertices.size();
	int intersects = 0;

	for (int i = 0; i < numFloats; i += 2) 
  {
		float x1 = vertices[i];
		float y1 = vertices[i + 1];
		float x2 = vertices[(i + 2) % numFloats];
		float y2 = vertices[(i + 3) % numFloats];
		if (((y1 <= y && y < y2) || (y2 <= y && y < y1)) && x < ((x2 - x1) / (y2 - y1) * (y - y1) + x1)) intersects++;
	}
	return (intersects & 1) == 1;
}

float Polygon::getX () 
{
	return m_x;
}

float Polygon::getY () 
{
	return m_y;
}

float Polygon::getOriginX () 
{
	return m_originX;
}

float Polygon::getOriginY () 
{
	return m_originY;
}

float Polygon::getRotation () 
{
	return m_rotation;
}

float Polygon::getScaleX () 
{
	return m_scaleX;
}

float Polygon::getScaleY () 
{
	return m_scaleY;
}