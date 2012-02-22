#include "stdafx.h"
#include "Plane.h"

Plane::Plane()
{
	//normal is (0, 0, 0)
	//distance is 0
	this->d = 0.f;
}

Plane::Plane( const Vector3& normal, float d) 
{
	this->normal.set(normal).nor();
	this->d = d;
}

Plane::Plane( const Vector3& normal, const Vector3& point) 
{
	this->normal.set(normal).nor();
	this->d = -this->normal.dot(point);
}

Plane::Plane( const Vector3& point1, const Vector3& point2, const Vector3& point3)
{
	set(point1, point2, point3);
}

void Plane::set( const Vector3& point1, const Vector3& point2, const Vector3& point3) 
{
	Vector3 l = point1.tmp().sub(point2);
	Vector3 r = point2.tmp2().sub(point3);
	Vector3 nor = l.crs(r).nor();
	normal.set(nor);
	d = -point1.dot(nor);
}

void Plane::set( float nx, float ny, float nz, float d) 
{
	normal.set(nx, ny, nz);
	this->d = d;
}

float Plane::distance( const Vector3& point) 
{
	return normal.dot(point) + d;
}

Plane::PlaneSide Plane::testPoint( const Vector3& point) 
{
	float dist = normal.dot(point) + d;

	if (dist == 0)
		return OnPlane;
	else if (dist < 0)
		return Back;
	else
		return Front;
}

bool Plane::isFrontFacing( const Vector3& direction) 
{
	float dot = normal.dot(direction);
	return dot <= 0;
}

Vector3& Plane::getNormal() 
{
	return normal;
}

float Plane::getD() 
{
	return d;
}

void Plane::set( const Vector3& point, const Vector3& normal) 
{
	this->normal.set(normal);
	d = -point.dot(normal);
}

void Plane::set(const Plane& plane) 
{
	this->normal.set(plane.normal);
	this->d = plane.d;
}

std::string Plane::toString() 
{
  std::stringstream ret;
  ret << normal.toString();
  ret << ", ";
  ret << d;
	return ret.str();
}