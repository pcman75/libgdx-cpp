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

/** Encapsulates a 3D vector. Allows chaining operations by returning a reference to it self in all modification methods.*/

class GdxDllImportExport Vector3
{
public:
	/** the x-component of this vector **/
	float x;
	/** the x-component of this vector **/
	float y;
	/** the x-component of this vector **/
	float z;
	
	static const Vector3& X;
	static const Vector3& Y;
	static const Vector3& Z;

private:
	static Vector3* m_tmp;
	static Vector3* m_tmp2;
	static Vector3* m_tmp3;

public:
	/** Constructs a vector at (0,0,0) */
	Vector3();

	/** Creates a vector with the given components
	 *
	 * @param x The x-component
	 * @param y The y-component
	 * @param z The z-component */
	Vector3(float x, float y, float z);

	/** Creates a vector from the given vector
	 *
	 * @param vector The vector */
	Vector3(const Vector3& vector);

	/** Creates a vector from the given array.
	 *
	 * @param values The array */
	Vector3(float values[3]);

	/** Sets the vector to the given components
	 *
	 * @param x The x-component
	 * @param y The y-component
	 * @param z The z-component
	 * @return this vector for chaining */
	Vector3& set(float x, float y, float z);

	/** Sets the components of the given vector
	 *
	 * @param vector The vector
	 * @return This vector for chaining */
	Vector3& set(const Vector3& vector);

	/** Sets the components from the array. The array must have at least 3 elements
	 *
	 * @param values The array
	 * @return this vector for chaining */
	Vector3& set(float values[3]);

	/** @return a copy of this vector */
	Vector3 cpy();


	/** NEVER EVER SAVE THIS REFERENCE! Do not use this unless you are aware of the side-effects, e.g. other methods might call this
	 * as well.
	 *
	 * @return a temporary copy of this vector */
	Vector3 tmp() const;

	/** NEVER EVER SAVE THIS REFERENCE! Do not use this unless you are aware of the side-effects, e.g. other methods might call this
	 * as well.
	 *
	 * @return a temporary copy of this vector */
	Vector3 tmp2() const;

	/** NEVER EVER SAVE THIS REFERENCE! Do not use this unless you are aware of the side-effects, e.g. other methods might call this
	 * as well.
	 *
	 * @return a temporary copy of this vector */
	Vector3 tmp3() const;

	/** Adds the given vector to this vector
	 *
	 * @param vector The other vector
	 * @return This vector for chaining */
	Vector3& add(const Vector3& vector);

	/** Adds the given vector to this component
	 * @param x The x-component of the other vector
	 * @param y The y-component of the other vector
	 * @param z The z-component of the other vector
	 * @return This vector for chaining. */
	Vector3& add(float x, float y, float z);

	/** Adds the given value to all three components of the vector.
	 *
	 * @param values The value
	 * @return This vector for chaining */
	Vector3& add(float values);

	/** Subtracts the given vector from this vector
	 * @param a_vec The other vector
	 * @return This vector for chaining */
	Vector3& sub(Vector3 a_vec);

	/** Subtracts the other vector from this vector.
	 *
	 * @param x The x-component of the other vector
	 * @param y The y-component of the other vector
	 * @param z The z-component of the other vector
	 * @return This vector for chaining */
	Vector3& sub(float x, float y, float z);

	/** Subtracts the given value from all components of this vector
	 *
	 * @param value The value
	 * @return This vector for chaining */
	Vector3& sub(float value);

	/** Multiplies all components of this vector by the given value
	 *
	 * @param value The value
	 * @return This vector for chaining */
	Vector3& mul(float value);

	/** Divides all components of this vector by the given value
	 *
	 * @param value The value
	 * @return This vector for chaining */
	Vector3& div(float value);

	/** @return The euclidian length */
	float len();

	/** @return The squared euclidian length */
	float len2();

	/** @param vector The other vector
	 * @return Wether this and the other vector are equal */
	bool idt(const Vector3& vector);

	/** @param vector The other vector
	 * @return The euclidian distance between this and the other vector */
	float dst(const Vector3& vector);

	/** Normalizes this vector to unit length
	 *
	 * @return This vector for chaining */
	Vector3& nor();

	/** @param vector The other vector
	 * @return The dot product between this and the other vector */
	float dot(const Vector3& vector) const;

	/** Sets this vector to the cross product between it and the other vector.
	 * @param vector The other vector
	 * @return This vector for chaining */
	Vector3& crs(const Vector3& vector);

	/** Sets this vector to the cross product between it and the other vector.
	 * @param x The x-component of the other vector
	 * @param y The y-component of the other vector
	 * @param z The z-component of the other vector
	 * @return This vector for chaining */
	Vector3& crs(float x, float y, float z);

	/** Multiplies the vector by the given matrix.
	 * @param matrix The matrix
	 * @return This vector for chaining */
	Vector3& mul(const class Matrix4& matrix);

	/** Multiplies this vector by the given matrix dividing by w. This is mostly used to project/unproject vectors via a perspective
	 * projection matrix.
	 *
	 * @param matrix The matrix.
	 * @return This vector for chaining */
	Vector3& prj(const class Matrix4& matrix);

	/** Multiplies this vector by the first three columns of the matrix, essentially only applying rotation and scaling.
	 *
	 * @param matrix The matrix
	 * @return This vector for chaining */
	Vector3& rot(const class Matrix4& matrix);

	/** @return Wether this vector is a unit length vector */
	bool isUnit();

	/** @return Wether this vector is a zero vector */
	bool isZero();

	/** Linearly interpolates between this vector and the target vector by alpha which is in the range [0,1]. The result is stored
	 * in this vector.
	 *
	 * @param target The target vector
	 * @param alpha The interpolation coefficient
	 * @return This vector for chaining. */
	Vector3 lerp(Vector3 target, float alpha);

	/** Spherically interpolates between this vector and the target vector by alpha which is in the range [0,1]. The result is
	 * stored in this vector.
	 *
	 * @param target The target vector
	 * @param alpha The interpolation coefficient
	 * @return This vector for chaining. */
	Vector3 slerp(Vector3 target, float alpha);

	/** {@inheritDoc} */
	std::string toString();

	/** Returns the dot product between this and the given vector.
	 *
	 * @param x The x-component of the other vector
	 * @param y The y-component of the other vector
	 * @param z The z-component of the other vector
	 * @return The dot product */
	float dot(float x, float y, float z) const;

	/** Returns the squared distance between this point and the given point
	 *
	 * @param point The other point
	 * @return The squared distance */
	float dst2(const Vector3& point);

	/** Returns the squared distance between this point and the given point
	 *
	 * @param x The x-component of the other point
	 * @param y The y-component of the other point
	 * @param z The z-component of the other point
	 * @return The squared distance */
	float dst2(float x, float y, float z);

	float dst(float x, float y, float z);

	/**
	 * Compares this vector with the other vector, using the supplied
	 * epsilon for fuzzy equality testing.
	 * @param obj
	 * @param epsilon
	 * @return whether the vectors are the same.
	 */
	bool epsilonEquals(const Vector3& obj, float epsilon);

	/** Scales the vector components by the given scalars.
	 *
	 * @param scalarX
	 * @param scalarY
	 * @param scalarZ */
	Vector3& scale(float scalarX, float scalarY, float scalarZ);
    
};

