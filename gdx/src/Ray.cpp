#include "stdafx.h"
#include "Ray.h"

Vector3 Ray::m_tmp;

/** Constructor, sets the starting position of the ray and the direction.
*
* @param origin The starting position
* @param direction The direction */
Ray::Ray(const Vector3& origin, const Vector3& direction)
{
	this->origin.set(origin);
	this->direction.set(direction).nor();
}

/** @return a copy of this ray. */
Ray Ray::cpy()
{
	return Ray(this->origin, this->direction);
}

/** Returns and endpoint given the distance. This is calculated as startpoint + distance * direction.
*
* @param distance The distance from the end point to the start point.
* @return The end point */
Vector3 Ray::getEndPoint(float distance)
{
	return Vector3(origin).add(direction.tmp().mul(distance));
}

/** Multiplies the ray by the given matrix. Use this to transform a ray into another coordinate system.
*
* @param matrix The matrix
* @return This ray for chaining. */
Ray& Ray::mul(const Matrix4& matrix)
{
	m_tmp.set(origin).add(direction);
	m_tmp.mul(matrix);
	origin.mul(matrix);
	direction.set(m_tmp.sub(origin));
	return *this;
}

/** {@inheritDoc} */
std::string Ray::toString ()
{
	return std::string("ray [") + origin.toString() + ":" + direction.toString() + "]";
}

/** Sets the starting position and the direction of this ray.
*
* @param origin The starting position
* @param direction The direction
* @return this ray for chaining */
Ray& Ray::set(const Vector3& origin, const Vector3& direction)
{
	this->origin.set(origin);
	this->direction.set(direction);
	return *this;
}

/** Sets this ray from the given starting position and direction.
*
* @param x The x-component of the starting position
* @param y The y-component of the starting position
* @param z The z-component of the starting position
* @param dx The x-component of the direction
* @param dy The y-component of the direction
* @param dz The z-component of the direction
* @return this ray for chaining */
Ray& Ray::set(float x, float y, float z, float dx, float dy, float dz)
{
	this->origin.set(x, y, z);
	this->direction.set(dx, dy, dz);
	return *this;
}

/** Sets the starting position and direction from the given ray
*
* @param ray The ray
* @return This ray for chaining */
Ray& Ray::set(const Ray& ray)
{

	this->origin.set(ray.origin);
	this->direction.set(ray.direction);
	return *this;
}

