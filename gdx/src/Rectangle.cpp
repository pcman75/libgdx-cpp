#include "stdafx.h"
#include "rectangle.h"

Rectangle::Rectangle() 
{
  x = y = 0;
	width = height = 0;
}

Rectangle::Rectangle( float x, float y, float width, float height) 
{
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
}

/** Constructs a rectangle based on the given rectangle
	* @param rect The rectangle */
Rectangle::Rectangle( const Rectangle& rect) 
{
	x = rect.x;
	y = rect.y;
	width = rect.width;
	height = rect.height;
}


float Rectangle::getX () 
{
	return x;
}

void Rectangle::setX( float x) 
{
	this->x = x;
}

float Rectangle::getY() 
{
	return y;
}

void Rectangle::setY( float y) 
{
	this->y = y;
}

float Rectangle::getWidth () 
{
	return width;
}

void Rectangle::setWidth( float width) 
{
	this->width = width;
}

float Rectangle::getHeight() 
{
	return height;
}

void Rectangle::setHeight( float height) 
{
	this->height = height;
}

bool Rectangle::contains( const Rectangle& rectangle) 
{
	float xmin = rectangle.x;
	float xmax = xmin + rectangle.width;

	float ymin = rectangle.y;
	float ymax = ymin + rectangle.height;

	return ((xmin > x && xmin < x + width) && (xmax > x && xmax < x + width))
		&& ((ymin > y && ymin < y + height) && (ymax > y && ymax < y + height));
}

bool Rectangle::overlaps( const Rectangle& rectangle) 
{
	return !(x > rectangle.x + rectangle.width || x + width < rectangle.x || y > rectangle.y + rectangle.height || y + height < rectangle.y);
}

void Rectangle::set( float x, float y, float width, float height) 
{
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
}

bool Rectangle::contains( float x, float y) 
{
	return this->x < x && this->x + this->width > x && this->y < y && this->y + this->height > y;
}

void Rectangle::set( const Rectangle& rect) 
{
	this->x = rect.x;
	this->y = rect.y;
	this->width = rect.width;
	this->height = rect.height;
}

void Rectangle::merge( const Rectangle& rect) 
{
	float minX = x < rect.x ? x : rect.x;
	float maxX = ( x + width) > ( rect.x + rect.width) ? ( x + width) : ( rect.x + rect.width);
	x = minX;
	width = maxX - minX;

	float minY = y < rect.y ? y : rect.y;
	float maxY = ( y + height) > ( rect.y + rect.height) ? ( y + height) : ( rect.y + rect.height);
	y = minY;
	height = maxY - minY;
}

std::string Rectangle::toString() 
{
  std::stringstream ret;
	ret << x;
  ret << ",";
  ret << y;
  ret << ",";
  ret << width;
  ret << ",";
  ret << height;
  ret << ",";
	return ret.str();
}
