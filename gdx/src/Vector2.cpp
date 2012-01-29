#include "StdAfx.h"
#include "Vector2.h"
#include "Matrix3.h"
#include "MathUtils.h"

Vector2 Vector2::m_tmp;

/** Constructs a new vector at (0,0) */
Vector2::Vector2()
{
	x = y = 0.f;
};

/** Constructs a vector with the given components
* @param x The x-component
* @param y The y-component */
Vector2::Vector2(float x, float y)
{
	this->x = x;
	this->y = y;
}

/** Constructs a vector from the given vector
* @param v The vector */
Vector2::Vector2(const Vector2& v)
{
	set(v);
}

/** @return a copy of this vector */
Vector2 Vector2::cpy()
{
	return *this;
}

/** @return The euclidian length */
float Vector2::len()
{
	return sqrt(x * x + y * y);
}

/** @return The squared euclidian length */
float Vector2::len2()
{
	return x * x + y * y;
}

/** Sets this vector from the given vector
* @param v The vector
* @return This vector for chaining */
Vector2& Vector2::set(const Vector2& v)
{
	x = v.x;
	y = v.y;
	return *this;
}

/** Sets the components of this vector
* @param x The x-component
* @param y The y-component
* @return This vector for chaining */
Vector2& Vector2::set(float x, float y)
{
	this->x = x;
	this->y = y;
	return *this;
}

/** Substracts the given vector from this vector.
* @param v The vector
* @return This vector for chaining */
Vector2& Vector2::sub(const Vector2& v)
{
	x -= v.x;
	y -= v.y;
	return *this;
}

/** Normalizes this vector
* @return This vector for chaining */
Vector2& Vector2::nor()
{
	float length = len();
	if(length != 0)
	{
		x /= length;
		y /= length;
	}
	return *this;
}

/** Adds the given vector to this vector
* @param v The vector
* @return This vector for chaining */
Vector2& Vector2::add(const Vector2& v)
{
	x += v.x;
	y += v.y;
	return *this;
}

/** Adds the given components to this vector
* @param x The x-component
* @param y The y-component
* @return This vector for chaining */
Vector2& Vector2::add(float x, float y)
{
	this->x += x;
	this->y += y;
	return *this;
}

/** @param v The other vector
* @return The dot product between this and the other vector */
float Vector2::dot(const Vector2& v)
{
	return x * v.x + y * v.y;
}

/** Multiplies this vector by a scalar
* @param scalar The scalar
* @return This vector for chaining */
Vector2& Vector2::mul(float scalar)
{
	x *= scalar;
	y *= scalar;
	return *this;
}

/** @param v The other vector
* @return the distance between this and the other vector */
float Vector2::dst(const Vector2& v)
{
	const float x_d = v.x - x;
	const float y_d = v.y - y;
	return sqrt(x_d * x_d + y_d * y_d);
}

/** @param x The x-component of the other vector
* @param y The y-component of the other vector
* @return the distance between this and the other vector */
float Vector2::dst(float x, float y)
{
	const float x_d = x - this->x;
	const float y_d = y - this->y;
	return sqrt(x_d * x_d + y_d * y_d);
}

/** @param v The other vector
* @return the squared distance between this and the other vector */
float Vector2::dst2(const Vector2& v)
{
	const float x_d = v.x - x;
	const float y_d = v.y - y;
	return x_d * x_d + y_d * y_d;
}

/** @param x The x-component of the other vector
* @param y The y-component of the other vector
* @return the squared distance between this and the other vector */
float Vector2::dst2(float x, float y)
{
	const float x_d = x - this->x;
	const float y_d = y - this->y;
	return x_d * x_d + y_d * y_d;
}

std::wstring Vector2::toString()
{
	std::wstringstream ret;
	ret << "[" << x << ":" << y << "]";
	return ret.str();
}

/** Substracts the other vector from this vector.
* @param x The x-component of the other vector
* @param y The y-component of the other vector
* @return This vector for chaining */
Vector2& Vector2::sub(float x, float y)
{
	this->x -= x;
	this->y -= y;
	return *this;
}

/** NEVER EVER SAVE THIS REFERENCE! Do not use this unless you are aware of the side-effects, e.g. other methods might call this
* as well.
*
* @return a temporary copy of this vector. Use with care as this is backed by a single static Vector2 instance. v1.tmp().add(
*         v2.tmp() ) will not work! */
Vector2& Vector2::tmp()
{
	return m_tmp.set(*this);
}

/** Multiplies this vector by the given matrix
* @param mat the matrix
* @return this vector */
Vector2& Vector2::mul(const Matrix3& mat)
{
	const float* const vals = mat.getValues();
	float x = this->x * vals[0] + this->y * vals[3] + vals[6];
	float y = this->x * vals[1] + this->y * vals[4] + vals[7];
	this->x = x;
	this->y = y;
	return *this;
}

/** Calculates the 2D cross product between this and the given vector.
* @param v the other vector
* @return the cross product */
float Vector2::crs(const Vector2& v)
{
	return this->x * v.y - this->y * v.x;
}

/** Calculates the 2D cross product between this and the given vector.
* @param x the x-coordinate of the other vector
* @param y the y-coordinate of the other vector
* @return the cross product */
float Vector2::crs(float x, float y)
{
	return this->x * y - this->y * x;
}

/** @return the angle in degrees of this vector (point) relative to the x-axis. Angles are counter-clockwise and between 0 and
*         360. */
float Vector2::angle()
{
	float angle = atan2(y, x) * MathUtils::radiansToDegrees;
	if(angle < 0) 
		angle += 360;
	return angle;
}

/** Rotates the Vector2 by the given angle, counter-clockwise.
* @param angle the angle in degrees
* @return the */
Vector2& Vector2::rotate(float angle)
{
	float rad = angle * MathUtils::degreesToRadians;
	float cosAngle = cos(rad);
	float sinAngle = sin(rad);

	float newX = this->x * cosAngle - this->y * sinAngle;
	float newY = this->x * sinAngle + this->y * cosAngle;

	this->x = newX;
	this->y = newY;

	return *this;
}

/** Linearly interpolates between this vector and the target vector by alpha which is in the range [0,1]. The result is stored
* in this vector.
*
* @param target The target vector
* @param alpha The interpolation coefficient
* @return This vector for chaining. */
Vector2& Vector2::lerp(const Vector2& target, float alpha)
{
	Vector2& r = this->mul(1.0f - alpha);
	r.add(tmp().mul(alpha));
	return r;
}

/**
* Compares this vector with the other vector, using the supplied
* epsilon for fuzzy equality testing.
* @param obj
* @param epsilon
* @return whether the vectors are the same.
*/
bool Vector2::epsilonEquals(const Vector2& obj, float epsilon)
{
	if(abs(obj.x - x) > epsilon) 
		return false;
	if(abs(obj.y - y) > epsilon) 
		return false;
	return true;
}

