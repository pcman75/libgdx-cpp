#include "stdafx.h"
#include "Rectangle.h"

/** Constructs a new rectangle with all values set to zero */
Rectangle::Rectangle()
{
}

/** Constructs a new rectangle with the given corner point in the bottom left and dimensions.
* @param x The corner point x-coordinate
* @param y The corner point y-coordinate
* @param width The width
* @param height The height */
Rectangle::Rectangle(float x, float y, float width, float height)
{
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
}

/** Constructs a rectangle based on the given rectangle
* @param rect The rectangle */
Rectangle::Rectangle(const Rectangle& rect)
{
	x = rect.x;
	y = rect.y;
	width = rect.width;
	height = rect.height;
}

/** @return the x-coordinate of the bottom left corner */
float Rectangle::getX ()
{
	return x;
}

/** Sets the x-coordinate of the bottom left corner
* @param x The x-coordinate */
void Rectangle::setX (float x)
{
	this->x = x;
}

/** @return the y-coordinate of the bottom left corner */
float Rectangle::getY ()
{
	return y;
}

/** Sets the y-coordinate of the bottom left corner
* @param y The y-coordinate */
void Rectangle::setY (float y)
{
	this->y = y;
}

/** @return the width */
float Rectangle::getWidth ()
{
	return width;
}

/** Sets the width of this rectangle
* @param width The width */
void Rectangle::setWidth (float width)
{
	this->width = width;
}

/** @return the height */
float Rectangle::getHeight ()
{
	return height;
}

/** Sets the height of this rectangle
* @param height The height */
void Rectangle::setHeight (float height)
{
	this->height = height;
}

/** @param rectangle the other {@link Rectangle}.
* @return whether the other rectangle is contained in this rectangle. */
bool Rectangle::contains(const Rectangle& rectangle)
{
	float xmin = rectangle.x;
	float xmax = xmin + rectangle.width;

	float ymin = rectangle.y;
	float ymax = ymin + rectangle.height;

	return ((xmin > x && xmin < x + width) && (xmax > x && xmax < x + width))
		&& ((ymin > y && ymin < y + height) && (ymax > y && ymax < y + height));
}

/** @param rectangle the other {@link Rectangle}
* @return whether this rectangle overlaps the other rectangle. */
bool Rectangle::overlaps(const Rectangle& rectangle)
{
	return !(x > rectangle.x + rectangle.width || x + width < rectangle.x || y > rectangle.y + rectangle.height || y + height < rectangle.y);
}

void Rectangle::set(float x, float y, float width, float height)
{
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
}

/** @param x point x coordinate
* @param y point y coordinate
* @return whether the point is contained in the rectangle */
bool Rectangle::contains (float x, float y)
{
	return this->x < x && this->x + this->width > x && this->y < y && this->y + this->height > y;
}

/** Sets the values of the given rectangle to this rectangle.
* @param rect the other rectangle */
void Rectangle::set(const Rectangle& rect)
{
	this->x = rect.x;
	this->y = rect.y;
	this->width = rect.width;
	this->height = rect.height;
}

/** Merges this rectangle with the other rectangle.
* @param rect the other rectangle */
void Rectangle::merge(const Rectangle& rect)
{
	float minX = min(x, rect.x);
	float maxX = max(x + width, rect.x + rect.width);
	x = minX;
	width = maxX - minX;

	float minY = min(y, rect.y);
	float maxY = max(y + height, rect.y + rect.height);
	y = minY;
	height = maxY - minY;
}

std::string Rectangle::toString ()
{
	std::stringstream ret;
	ret << x << "," << y << "," << width << "," << height;
	return ret.str();
}

