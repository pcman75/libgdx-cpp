/*******************************************************************************
 * Copyright 2011 See AUTHORS file.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 ******************************************************************************/

#pragma once
#include "GdxDefines.h"

/** A simple quaternion class. See http://en.wikipedia.org/wiki/Quaternion for more information.
*/
class GdxDllImportExport Quaternion
{
private:
	static const float NORMALIZATION_TOLERANCE;
	static Quaternion m_tmp1;
	static Quaternion m_tmp2;

public:
	float x;
	float y;
	float z;
	float w;

	/** Constructor, sets the four components of the quaternion.
	 * @param x The x-component
	 * @param y The y-component
	 * @param z The z-component
	 * @param w The w-component */
	Quaternion(float x, float y, float z, float w);

	Quaternion();

	/** Constructor, sets the quaternion components from the given quaternion.
	 *
	 * @param quaternion The quaternion to copy. */
	Quaternion(const Quaternion& quaternion);

	/** Constructor, sets the quaternion from the given axis vector and the angle around that axis in degrees.
	 *
	 * @param axis The axis
	 * @param angle The angle in degrees. */
	Quaternion(const class Vector3& axis, float angle);

	/** Sets the components of the quaternion
	 * @param x The x-component
	 * @param y The y-component
	 * @param z The z-component
	 * @param w The w-component
	 * @return This quaternion for chaining */
	Quaternion& set(float x, float y, float z, float w);

	/** Sets the quaternion components from the given quaternion.
	 * @param quaternion The quaternion.
	 * @return This quaternion for chaining. */
	Quaternion& set(const Quaternion& quaternion);


	/** Sets the quaternion components from the given axis and angle around that axis.
	 *
	 * @param axis The axis
	 * @param angle The angle in degrees
	 * @return This quaternion for chaining. */
	Quaternion& set(const class Vector3& axis, float angle);

	/** @return a copy of this quaternion */
	Quaternion& cpy();

	/** @return the euclidian length of this quaternion */
	float len();

	/** {@inheritDoc} */
	std::string toString();

	/** Sets the quaternion to the given euler angles.
	 * @param yaw the yaw in degrees
	 * @param pitch the pitch in degress
	 * @param roll the roll in degess
	 * @return this quaternion */
	Quaternion& setEulerAngles(float yaw, float pitch, float roll);

	/** @return the length of this quaternion without square root */
	float len2();

	/** Normalizes this quaternion to unit length
	 * @return the quaternion for chaining */
	Quaternion& nor();

	/** Conjugate the quaternion.
	 *
	 * @return This quaternion for chaining */
	Quaternion conjugate();

	// TODO : this would better fit into the vector3 class
	/** Transforms the given vector using this quaternion
	 *
	 * @param v Vector to transform */
	void transform(class Vector3& v);

	/** Multiplies this quaternion with another one
	 *
	 * @param q Quaternion to multiply with
	 * @return This quaternion for chaining */
	Quaternion& mul(const Quaternion& q);

	/** Multiplies this quaternion with another one in the form of q * this
	 *
	 * @param q Quaternion to multiply with
	 * @return This quaternion for chaining */
	Quaternion& mulLeft(const Quaternion& q);

	// TODO : the matrix4 set(quaternion) doesnt set the last row+col of the matrix to 0,0,0,1 so... that's why there is this
// method
	/** Fills a 4x4 matrix with the rotation matrix represented by this quaternion.
	 *
	 * @param matrix Matrix to fill */
	void toMatrix(float matrix[16]);

	/** Returns the identity quaternion x,y,z = 0 and w=1
	 *
	 * @return Identity quaternion */
	static Quaternion idt();

	// todo : the setFromAxis(v3,float) method should replace the set(v3,float) method
	/** Sets the quaternion components from the given axis and angle around that axis.
	 *
	 * @param axis The axis
	 * @param angle The angle in degrees
	 * @return This quaternion for chaining. */
	Quaternion& setFromAxis(const Vector3& axis, float angle);

	/** Sets the quaternion components from the given axis and angle around that axis.
	 *
	 * @param x X direction of the axis
	 * @param y Y direction of the axis
	 * @param z Z direction of the axis
	 * @param angle The angle in degrees
	 * @return This quaternion for chaining. */
	Quaternion& setFromAxis(float x, float y, float z, float angle);

// fromRotationMatrix(xAxis.x, yAxis.x, zAxis.x, xAxis.y, yAxis.y, zAxis.y,
// xAxis.z, yAxis.z, zAxis.z);

// const float m00, const float m01, const float m02, const float m10,
// const float m11, const float m12, const float m20, const float m21, const float m22

	Quaternion& setFromMatrix(const class Matrix4& matrix);

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
	Quaternion& setFromAxes(float xx, float xy, float xz, float yx, float yy, float yz, float zx, float zy, float zz);

	/** Spherical linear interpolation between this quaternion and the other quaternion, based on the alpha value in the range
	 * [0,1]. Taken from. Taken from Bones framework for JPCT, see http://www.aptalkarga.com/bones/
	 * @param end the end quaternion
	 * @param alpha alpha in the range [0,1]
	 * @return this quaternion for chaining */
	Quaternion& slerp(Quaternion end, float alpha);

	bool operator==(const Quaternion& o);
	bool equals(const Quaternion& o);

	/** Dot product between this and the other quaternion.
	 * @param other the other quaternion.
	 * @return this quaternion for chaining. */
	float dot(const Quaternion& other);

	/** Multiplies the components of this quaternion with the given scalar.
	 * @param scalar the scalar.
	 * @return this quaternion for chaining. */
	Quaternion& mul(float scalar);

	private:
		float toRadians(float angle);
};
