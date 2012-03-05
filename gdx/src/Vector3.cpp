#include "StdAfx.h"
#include "Vector3.h"
#include "Matrix4.h"

const Vector3& Vector3::X = Vector3(1, 0, 0);
const Vector3& Vector3::Y = Vector3(0, 1, 0);
const Vector3& Vector3::Z = Vector3(0, 0, 1);

Vector3* Vector3::m_tmp = new Vector3();
Vector3* Vector3::m_tmp2 = new Vector3();
Vector3* Vector3::m_tmp3 = new Vector3();

Vector3::Vector3()
{
	x = y = z = 0;
}

/** Creates a vector with the given components
*
* @param x The x-component
* @param y The y-component
* @param z The z-component */
Vector3::Vector3(float x, float y, float z)
{
	set(x, y, z);
}

/** Creates a vector from the given vector
*
* @param vector The vector */
Vector3::Vector3(const Vector3& vector)
{
	set(vector);
}

/** Creates a vector from the given array.
*
* @param values The array */
Vector3::Vector3(float values[3])
{
	set(values[0], values[1], values[2]);
}

/** Sets the vector to the given components
*
* @param x The x-component
* @param y The y-component
* @param z The z-component
* @return this vector for chaining */
Vector3& Vector3::set(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
	return *this;
}

/** Sets the components of the given vector
*
* @param vector The vector
* @return This vector for chaining */
Vector3& Vector3::set(const Vector3& vector)
{
	return set(vector.x, vector.y, vector.z);
}

/** Sets the components from the array. The array must have at least 3 elements
*
* @param values The array
* @return this vector for chaining */
Vector3& Vector3::set(float values[3])
{
	return set(values[0], values[1], values[2]);
}

/** @return a copy of this vector */
Vector3 Vector3::cpy()
{
	return *this;
}


/** NEVER EVER SAVE THIS REFERENCE! Do not use this unless you are aware of the side-effects, e.g. other methods might call this
* as well.
*
* @return a temporary copy of this vector */
Vector3 Vector3::tmp() const
{
	return m_tmp->set(*this);
}

/** NEVER EVER SAVE THIS REFERENCE! Do not use this unless you are aware of the side-effects, e.g. other methods might call this
* as well.
*
* @return a temporary copy of this vector */
Vector3 Vector3::tmp2() const
{
	return m_tmp2->set(*this);
}

/** NEVER EVER SAVE THIS REFERENCE! Do not use this unless you are aware of the side-effects, e.g. other methods might call this
* as well.
*
* @return a temporary copy of this vector */
Vector3 Vector3::tmp3() const
{
	return m_tmp3->set(*this);
}

/** Adds the given vector to this vector
*
* @param vector The other vector
* @return This vector for chaining */
Vector3& Vector3::add(const Vector3& vector)
{
	return add(vector.x, vector.y, vector.z);
}

/** Adds the given vector to this component
* @param x The x-component of the other vector
* @param y The y-component of the other vector
* @param z The z-component of the other vector
* @return This vector for chaining. */
Vector3& Vector3::add(float x, float y, float z)
{
	return set(this->x + x, this->y + y, this->z + z);
}

/** Adds the given value to all three components of the vector.
*
* @param values The value
* @return This vector for chaining */
Vector3& Vector3::add(float values)
{
	return this->set(this->x + values, this->y + values, this->z + values);
}

/** Subtracts the given vector from this vector
* @param a_vec The other vector
* @return This vector for chaining */
Vector3& Vector3::sub(Vector3 a_vec)
{
	return sub(a_vec.x, a_vec.y, a_vec.z);
}

/** Subtracts the other vector from this vector.
*
* @param x The x-component of the other vector
* @param y The y-component of the other vector
* @param z The z-component of the other vector
* @return This vector for chaining */
Vector3& Vector3::sub(float x, float y, float z)
{
	return set(this->x - x, this->y - y, this->z - z);
}

/** Subtracts the given value from all components of this vector
*
* @param value The value
* @return This vector for chaining */
Vector3& Vector3::sub(float value)
{
	return set(this->x - value, this->y - value, this->z - value);
}

/** Multiplies all components of this vector by the given value
*
* @param value The value
* @return This vector for chaining */
Vector3& Vector3::mul(float value)
{
	return set(this->x * value, this->y * value, this->z * value);
}

/** Divides all components of this vector by the given value
*
* @param value The value
* @return This vector for chaining */
Vector3& Vector3::div(float value)
{
	float d = 1 / value;
	return set(this->x * d, this->y * d, this->z * d);
}

/** @return The euclidian length */
float Vector3::len()
{
	return sqrt(x * x + y * y + z * z);
}

/** @return The squared euclidian length */
float Vector3::len2()
{
	return x * x + y * y + z * z;
}

/** @param vector The other vector
* @return Wether this and the other vector are equal */
bool Vector3::idt(const Vector3& vector)
{
	return x == vector.x && y == vector.y && z == vector.z;
}

/** @param vector The other vector
* @return The euclidian distance between this and the other vector */
float Vector3::dst(const Vector3& vector)
{
	float a = vector.x - x;
	float b = vector.y - y;
	float c = vector.z - z;

	a *= a;
	b *= b;
	c *= c;

	return sqrt(a + b + c);
}

/** Normalizes this vector to unit length
*
* @return This vector for chaining */
Vector3& Vector3::nor()
{
	float len = this->len();
	if(len == 0)
	{
		return *this;
	}
	else
	{
		return div(len);
	}
}

/** @param vector The other vector
* @return The dot product between this and the other vector */
float Vector3::dot(const Vector3& vector) const
{
	return x * vector.x + y * vector.y + z * vector.z;
}

/** Sets this vector to the cross product between it and the other vector.
* @param vector The other vector
* @return This vector for chaining */
Vector3& Vector3::crs(const Vector3& vector)
{
	return set(y * vector.z - z * vector.y, z * vector.x - x * vector.z, x * vector.y - y * vector.x);
}

/** Sets this vector to the cross product between it and the other vector.
* @param x The x-component of the other vector
* @param y The y-component of the other vector
* @param z The z-component of the other vector
* @return This vector for chaining */
Vector3& Vector3::crs(float x, float y, float z)
{
	return set(this->y * z - this->z * y, this->z * x - this->x * z, this->x * y - this->y * x);
}

/** Multiplies the vector by the given matrix.
* @param matrix The matrix
* @return This vector for chaining */
Vector3& Vector3::mul(const Matrix4& matrix)
{
	const float* const l_mat = matrix.getValues();
	return this->set(x * l_mat[Matrix4::M00] + y * l_mat[Matrix4::M01] + z * l_mat[Matrix4::M02] + l_mat[Matrix4::M03], x
		* l_mat[Matrix4::M10] + y * l_mat[Matrix4::M11] + z * l_mat[Matrix4::M12] + l_mat[Matrix4::M13], x * l_mat[Matrix4::M20] + y
		* l_mat[Matrix4::M21] + z * l_mat[Matrix4::M22] + l_mat[Matrix4::M23]);
}

/** Multiplies this vector by the given matrix dividing by w. This is mostly used to project/unproject vectors via a perspective
* projection matrix.
*
* @param matrix The matrix.
* @return This vector for chaining */
Vector3& Vector3::prj(const Matrix4& matrix)
{
	const float* const l_mat = matrix.getValues();
	float l_w = x * l_mat[Matrix4::M30] + y * l_mat[Matrix4::M31] + z * l_mat[Matrix4::M32] + l_mat[Matrix4::M33];
	return this->set((x * l_mat[Matrix4::M00] + y * l_mat[Matrix4::M01] + z * l_mat[Matrix4::M02] + l_mat[Matrix4::M03]) / l_w, (x
		* l_mat[Matrix4::M10] + y * l_mat[Matrix4::M11] + z * l_mat[Matrix4::M12] + l_mat[Matrix4::M13])
		/ l_w, (x * l_mat[Matrix4::M20] + y * l_mat[Matrix4::M21] + z * l_mat[Matrix4::M22] + l_mat[Matrix4::M23]) / l_w);
}

/** Multiplies this vector by the first three columns of the matrix, essentially only applying rotation and scaling.
*
* @param matrix The matrix
* @return This vector for chaining */
Vector3& Vector3::rot(const Matrix4& matrix)
{
	const float* const l_mat = matrix.getValues();
	return this->set(x * l_mat[Matrix4::M00] + y * l_mat[Matrix4::M01] + z * l_mat[Matrix4::M02], x * l_mat[Matrix4::M10] + y
		* l_mat[Matrix4::M11] + z * l_mat[Matrix4::M12], x * l_mat[Matrix4::M20] + y * l_mat[Matrix4::M21] + z * l_mat[Matrix4::M22]);
}

/** @return Wether this vector is a unit length vector */
bool Vector3::isUnit()
{
	return this->len() == 1;
}

/** @return Wether this vector is a zero vector */
bool Vector3::isZero()
{
	return x == 0 && y == 0 && z == 0;
}

/** Linearly interpolates between this vector and the target vector by alpha which is in the range [0,1]. The result is stored
* in this vector.
*
* @param target The target vector
* @param alpha The interpolation coefficient
* @return This vector for chaining. */
Vector3 Vector3::lerp(Vector3 target, float alpha)
{
	Vector3 r = this->mul(1.0f - alpha);
	r.add(target.tmp().mul(alpha));
	return r;
}

/** Spherically interpolates between this vector and the target vector by alpha which is in the range [0,1]. The result is
* stored in this vector.
*
* @param target The target vector
* @param alpha The interpolation coefficient
* @return This vector for chaining. */
Vector3 Vector3::slerp(Vector3 target, float alpha)
{
	float dotValue = dot(target);
	if(dotValue > 0.99995 || dotValue < 0.9995)
	{
		this->add(target.tmp().sub(*this).mul(alpha));
		this->nor();
		return *this;
	}

	if(dotValue > 1) dotValue = 1;
	if(dotValue < -1) dotValue = -1;

	float theta0 = acos(dotValue);
	float theta = theta0 * alpha;
	Vector3 v2 = target.tmp().sub(x * dotValue, y * dotValue, z * dotValue);
	v2.nor();
	return this->mul(cos(theta)).add(v2.mul(sin(theta))).nor();
}

/** {@inheritDoc} */
std::string Vector3::toString()
{
	std::stringstream ret;
	ret << x << "," << y << "," << z;
	return ret.str();
}

/** Returns the dot product between this and the given vector.
*
* @param x The x-component of the other vector
* @param y The y-component of the other vector
* @param z The z-component of the other vector
* @return The dot product */
float Vector3::dot(float x, float y, float z) const
{
	return this->x * x + this->y * y + this->z * z;
}

/** Returns the squared distance between this point and the given point
*
* @param point The other point
* @return The squared distance */
float Vector3::dst2(const Vector3& point)
{

	float a = point.x - x;
	float b = point.y - y;
	float c = point.z - z;

	a *= a;
	b *= b;
	c *= c;

	return a + b + c;
}

/** Returns the squared distance between this point and the given point
*
* @param x The x-component of the other point
* @param y The y-component of the other point
* @param z The z-component of the other point
* @return The squared distance */
float Vector3::dst2(float x, float y, float z)
{
	float a = x - this->x;
	float b = y - this->y;
	float c = z - this->z;

	a *= a;
	b *= b;
	c *= c;

	return a + b + c;
}

float Vector3::dst(float x, float y, float z)
{
	return sqrt(dst2(x, y, z));
}

/**
* Compares this vector with the other vector, using the supplied
* epsilon for fuzzy equality testing.
* @param obj
* @param epsilon
* @return whether the vectors are the same.
*/
bool Vector3::epsilonEquals(const Vector3& obj, float epsilon)
{
	if(abs(obj.x - x) > epsilon) 
		return false;
	if(abs(obj.y - y) > epsilon) 
		return false;
	if(abs(obj.z - z) > epsilon) 
		return false;
	return true;
}

/** Scales the vector components by the given scalars.
*
* @param scalarX
* @param scalarY
* @param scalarZ */
Vector3& Vector3::scale(float scalarX, float scalarY, float scalarZ)
{
	x *= scalarX;
	y *= scalarY;
	z *= scalarZ;
	return *this;
}