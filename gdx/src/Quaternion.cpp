#include "StdAfx.h"
#include "Quaternion.h"
#include "Vector3.h"
#include "Matrix4.h"
#include "MathUtils.h"

const float Quaternion::NORMALIZATION_TOLERANCE = 0.00001f;
Quaternion Quaternion::m_tmp1 = Quaternion(0, 0, 0, 0);
Quaternion Quaternion::m_tmp2 = Quaternion(0, 0, 0, 0);


Quaternion::Quaternion(float x, float y, float z, float w)
{
	set(x, y, z, w);
}

Quaternion::Quaternion()
{
	set(0.f, 0.f, 0.f, 0.f);
}

/** Constructor, sets the quaternion components from the given quaternion.
*
* @param quaternion The quaternion to copy. */
Quaternion::Quaternion(const Quaternion& quaternion)
{
	set(quaternion);
}

/** Constructor, sets the quaternion from the given axis vector and the angle around that axis in degrees.
*
* @param axis The axis
* @param angle The angle in degrees. */
Quaternion::Quaternion(const class Vector3& axis, float angle)
{
	set(axis, angle);
}

/** Sets the components of the quaternion
* @param x The x-component
* @param y The y-component
* @param z The z-component
* @param w The w-component
* @return This quaternion for chaining */
Quaternion& Quaternion::set(float x, float y, float z, float w)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
	return *this;
}

/** Sets the quaternion components from the given quaternion.
* @param quaternion The quaternion.
* @return This quaternion for chaining. */
Quaternion& Quaternion::set(const Quaternion& quaternion)
{
	return set(quaternion.x, quaternion.y, quaternion.z, quaternion.w);
}


/** Sets the quaternion components from the given axis and angle around that axis.
*
* @param axis The axis
* @param angle The angle in degrees
* @return This quaternion for chaining. */
Quaternion& Quaternion::set(const Vector3& axis, float angle)
{
	float l_ang = toRadians(angle);
	float l_sin = sin(l_ang / 2);
	float l_cos = cos(l_ang / 2);
	return set(axis.x * l_sin, axis.y * l_sin, axis.z * l_sin, l_cos).nor();
}

/** @return a copy of this quaternion */
Quaternion& Quaternion::cpy()
{
	return *this;
}

/** @return the euclidian length of this quaternion */
float Quaternion::len()
{
	return sqrt(x * x + y * y + z * z + w * w);
}

/** {@inheritDoc} */
std::string Quaternion::toString()
{
	std::stringstream ret;
	ret << "[" << x << "|" << y << "|" << z << "|" << w << "]";
	return ret.str();
}

/** Sets the quaternion to the given euler angles.
* @param yaw the yaw in degrees
* @param pitch the pitch in degress
* @param roll the roll in degess
* @return this quaternion */
Quaternion& Quaternion::setEulerAngles(float yaw, float pitch, float roll)
{
	yaw = toRadians(yaw);
	pitch = toRadians(pitch);
	roll = toRadians(roll);
	float num9 = roll * 0.5f;
	float num6 = sin(num9);
	float num5 = cos(num9);
	float num8 = pitch * 0.5f;
	float num4 = sin(num8);
	float num3 = cos(num8);
	float num7 = yaw * 0.5f;
	float num2 = sin(num7);
	float num = cos(num7);
	x = ((num * num4) * num5) + ((num2 * num3) * num6);
	y = ((num2 * num3) * num5) - ((num * num4) * num6);
	z = ((num * num3) * num6) - ((num2 * num4) * num5);
	w = ((num * num3) * num5) + ((num2 * num4) * num6);
	return *this;
}

/** @return the length of this quaternion without square root */
float Quaternion::len2()
{
	return x * x + y * y + z * z + w * w;
}

/** Normalizes this quaternion to unit length
* @return the quaternion for chaining */
Quaternion& Quaternion::nor()
{
	float len = len2();
	if(len != 0.f && (abs(len - 1.0f) > NORMALIZATION_TOLERANCE))
	{
		len = sqrt(len);
		w /= len;
		x /= len;
		y /= len;
		z /= len;
	}
	return *this;
}

/** Conjugate the quaternion.
*
* @return This quaternion for chaining */
Quaternion Quaternion::conjugate()
{
	x = -x;
	y = -y;
	z = -z;
	return *this;
}

// TODO : this would better fit into the vector3 class
/** Transforms the given vector using this quaternion
*
* @param v Vector to transform */
void Quaternion::transform(class Vector3& v)
{
	m_tmp2.set(*this);
	m_tmp2.conjugate();
	m_tmp2.mulLeft(m_tmp1.set(v.x, v.y, v.z, 0)).mulLeft(*this);

	v.x = m_tmp2.x;
	v.y = m_tmp2.y;
	v.z = m_tmp2.z;
}

/** Multiplies this quaternion with another one
*
* @param q Quaternion to multiply with
* @return This quaternion for chaining */
Quaternion& Quaternion::mul(const Quaternion& q)
{
	float newX = w * q.x + x * q.w + y * q.z - z * q.y;
	float newY = w * q.y + y * q.w + z * q.x - x * q.z;
	float newZ = w * q.z + z * q.w + x * q.y - y * q.x;
	float newW = w * q.w - x * q.x - y * q.y - z * q.z;
	x = newX;
	y = newY;
	z = newZ;
	w = newW;
	return *this;
}

/** Multiplies this quaternion with another one in the form of q * this
*
* @param q Quaternion to multiply with
* @return This quaternion for chaining */
Quaternion& Quaternion::mulLeft(const Quaternion& q)
{
	float newX = q.w * x + q.x * w + q.y * z - q.z * y;
	float newY = q.w * y + q.y * w + q.z * x - q.x * z;
	float newZ = q.w * z + q.z * w + q.x * y - q.y * x;
	float newW = q.w * w - q.x * x - q.y * y - q.z * z;
	x = newX;
	y = newY;
	z = newZ;
	w = newW;
	return *this;
}

// TODO : the matrix4 set(quaternion) doesnt set the last row+col of the matrix to 0,0,0,1 so... that's why there is this
// method
/** Fills a 4x4 matrix with the rotation matrix represented by this quaternion.
*
* @param matrix Matrix to fill */
void Quaternion::toMatrix(float matrix[16])
{
	float xx = x * x;
	float xy = x * y;
	float xz = x * z;
	float xw = x * w;
	float yy = y * y;
	float yz = y * z;
	float yw = y * w;
	float zz = z * z;
	float zw = z * w;

	// Set matrix from quaternion
	matrix[Matrix4::M00] = 1 - 2 * (yy + zz);
	matrix[Matrix4::M01] = 2 * (xy - zw);
	matrix[Matrix4::M02] = 2 * (xz + yw);
	matrix[Matrix4::M03] = 0;
	matrix[Matrix4::M10] = 2 * (xy + zw);
	matrix[Matrix4::M11] = 1 - 2 * (xx + zz);
	matrix[Matrix4::M12] = 2 * (yz - xw);
	matrix[Matrix4::M13] = 0;
	matrix[Matrix4::M20] = 2 * (xz - yw);
	matrix[Matrix4::M21] = 2 * (yz + xw);
	matrix[Matrix4::M22] = 1 - 2 * (xx + yy);
	matrix[Matrix4::M23] = 0;
	matrix[Matrix4::M30] = 0;
	matrix[Matrix4::M31] = 0;
	matrix[Matrix4::M32] = 0;
	matrix[Matrix4::M33] = 1;
}

/** Returns the identity quaternion x,y,z = 0 and w=1
*
* @return Identity quaternion */
Quaternion  Quaternion::idt()
{
	return Quaternion(0, 0, 0, 1);
}

// todo : the setFromAxis(v3,float) method should replace the set(v3,float) method
/** Sets the quaternion components from the given axis and angle around that axis.
*
* @param axis The axis
* @param angle The angle in degrees
* @return This quaternion for chaining. */
Quaternion& Quaternion::setFromAxis(const Vector3& axis, float angle)
{
	return setFromAxis(axis.x, axis.y, axis.z, angle);
}

/** Sets the quaternion components from the given axis and angle around that axis.
*
* @param x X direction of the axis
* @param y Y direction of the axis
* @param z Z direction of the axis
* @param angle The angle in degrees
* @return This quaternion for chaining. */
Quaternion& Quaternion::setFromAxis(float x, float y, float z, float angle)
{
	const float l_ang = angle * MathUtils::degreesToRadians;
	float l_sin = MathUtils::sin(l_ang / 2);
	float l_cos = MathUtils::cos(l_ang / 2);
	return set(x * l_sin, y * l_sin, z * l_sin, l_cos).nor();
}

// fromRotationMatrix(xAxis.x, yAxis.x, zAxis.x, xAxis.y, yAxis.y, zAxis.y,
// xAxis.z, yAxis.z, zAxis.z);

// const float m00, const float m01, const float m02, const float m10,
// const float m11, const float m12, const float m20, const float m21, const float m22

Quaternion& Quaternion::setFromMatrix(const Matrix4& matrix)
{
	return setFromAxes(matrix.val[Matrix4::M00], matrix.val[Matrix4::M01], matrix.val[Matrix4::M02], matrix.val[Matrix4::M10],
		matrix.val[Matrix4::M11], matrix.val[Matrix4::M12], matrix.val[Matrix4::M20], matrix.val[Matrix4::M21],
		matrix.val[Matrix4::M22]);
}

/** <p>
* Sets the Quaternion from the given x-, y- and z-axis which have to be orthonormal.
* </p>
*
* <p>
* Taken from Bones framework for JPCT, see http://www.aptalkarga.com/bones/ which in turn took it from Graphics Gem code at
* ftp://ftp.cis.upenn.edu/pub/graphics/shoemake/quatut.ps.Z.
* </p>
*
* @param xx x-axis x-coordinate
* @param xy x-axis y-coordinate
* @param xz x-axis z-coordinate
* @param yx y-axis x-coordinate
* @param yy y-axis y-coordinate
* @param yz y-axis z-coordinate
* @param zx z-axis x-coordinate
* @param zy z-axis y-coordinate
* @param zz z-axis z-coordinate */
Quaternion& Quaternion::setFromAxes(float xx, float xy, float xz, float yx, float yy, float yz, float zx, float zy, float zz)
{
	// the trace is the sum of the diagonal elements; see
	// http://mathworld.wolfram.com/MatrixTrace.html
	const float m00 = xx, m01 = yx, m02 = zx;
	const float m10 = xy, m11 = yy, m12 = zy;
	const float m20 = xz, m21 = yz, m22 = zz;
	const float t = m00 + m11 + m22;

	// we protect the division by s by ensuring that s>=1
	double x, y, z, w;
	if(t >= 0)    // |w| >= .5
	{
		double s = sqrt(t + 1); // |s|>=1 ...
		w = 0.5 * s;
		s = 0.5 / s; // so this division isn't bad
		x = (m21 - m12) * s;
		y = (m02 - m20) * s;
		z = (m10 - m01) * s;
	}
	else if((m00 > m11) && (m00 > m22))
	{
		double s = sqrt(1.0 + m00 - m11 - m22); // |s|>=1
		x = s * 0.5; // |x| >= .5
		s = 0.5 / s;
		y = (m10 + m01) * s;
		z = (m02 + m20) * s;
		w = (m21 - m12) * s;
	}
	else if(m11 > m22)
	{
		double s = sqrt(1.0 + m11 - m00 - m22); // |s|>=1
		y = s * 0.5; // |y| >= .5
		s = 0.5 / s;
		x = (m10 + m01) * s;
		z = (m21 + m12) * s;
		w = (m02 - m20) * s;
	}
	else
	{
		double s = sqrt(1.0 + m22 - m00 - m11); // |s|>=1
		z = s * 0.5; // |z| >= .5
		s = 0.5 / s;
		x = (m02 + m20) * s;
		y = (m21 + m12) * s;
		w = (m10 - m01) * s;
	}

	return set((float)x, (float)y, (float)z, (float)w);
}

/** Spherical linear interpolation between this quaternion and the other quaternion, based on the alpha value in the range
* [0,1]. Taken from. Taken from Bones framework for JPCT, see http://www.aptalkarga.com/bones/
* @param end the end quaternion
* @param alpha alpha in the range [0,1]
* @return this quaternion for chaining */
Quaternion& Quaternion::slerp(Quaternion end, float alpha)
{
	if(equals(end))
	{
		return *this;
	}

	float result = dot(end);

	if(result < 0.0)
	{
		// Negate the second quaternion and the result of the dot product
		end.mul(-1);
		result = -result;
	}

	// Set the first and second scale for the interpolation
	float scale0 = 1 - alpha;
	float scale1 = alpha;

	// Check if the angle between the 2 quaternions was big enough to
	// warrant such calculations
	if((1 - result) > 0.1)   // Get the angle between the 2 quaternions,
	{
		// and then store the sin() of that angle
		const double theta = acos(result);
		const double invSinTheta = 1.f / sin(theta);

		// Calculate the scale for q1 and q2, according to the angle and
		// it's sine value
		scale0 = (float)(sin((1 - alpha) * theta) * invSinTheta);
		scale1 = (float)(sin((alpha * theta)) * invSinTheta);
	}

	// Calculate the x, y, z and w values for the quaternion by using a
	// special form of linear interpolation for quaternions.
	const float x = (scale0 * this->x) + (scale1 * end.x);
	const float y = (scale0 * this->y) + (scale1 * end.y);
	const float z = (scale0 * this->z) + (scale1 * end.z);
	const float w = (scale0 * this->w) + (scale1 * end.w);
	set(x, y, z, w);

	// Return the interpolated quaternion
	return *this;
}

bool Quaternion::operator==(const Quaternion& o)
{
	if(this == &o)
	{
		return true;
	}
	return x == o.x && y == o.y && z == o.z && w == o.w;
}

bool Quaternion::equals(const Quaternion& o)
{
	return *this == o;
}


/** Dot product between this and the other quaternion.
* @param other the other quaternion.
* @return this quaternion for chaining. */
float Quaternion::dot(const Quaternion& other)
{
	return x * other.x + y * other.y + z * other.z + w * other.w;
}

/** Multiplies the components of this quaternion with the given scalar.
* @param scalar the scalar.
* @return this quaternion for chaining. */
Quaternion& Quaternion::mul(float scalar)
{
	this->x *= scalar;
	this->y *= scalar;
	this->z *= scalar;
	this->w *= scalar;
	return *this;
}

float Quaternion::toRadians(float angle)
{
	return ( float) ( angle * M_PI / 180);
}
