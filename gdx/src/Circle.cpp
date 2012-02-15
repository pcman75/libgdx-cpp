#include "stdafx.h"
#include "circle.h"

Circle::Circle( float x, float y, float radius) 
{
	this->x = x;
	this->y = y;
	this->radius = radius;
}

Circle::Circle( Vector2 position, float radius) 
{
	this->x = position.x;
	this->y = position.y;
	this->radius = radius;
}

bool Circle::contains (float x, float y) 
{
	x = this->x - x;
	y = this->y - y;
	return x * x + y * y <= radius * radius;
}

bool Circle::contains( Vector2 point) 
{
	float x = this->x - point.x;
	float y = this->y - point.y;
	return x * x + y * y <= radius * radius;
}

void Circle::set (float x, float y, float radius) 
{
	this->x = x;
	this->y = y;
	this->radius = radius;
}

