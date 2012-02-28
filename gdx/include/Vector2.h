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


/** Encapsulates a 2D vector. Allows chaining methods by returning a reference to itself
 * @author badlogicgames@gmail.com */
class GdxDllImportExport Vector2
{
public:
	/** Static temporary vector. Use with care! Use only when sure other code will not also use this.
	 * @see #tmp() **/
	static Vector2 m_tmp;

	/** the x-component of this vector **/
	float x;
	/** the y-component of this vector **/
	float y;

	/** Constructs a new vector at (0,0) */
	Vector2();

	/** Constructs a vector with the given components
	 * @param x The x-component
	 * @param y The y-component */
	Vector2(float x, float y);

	/** Constructs a vector from the given vector
	 * @param v The vector */
	Vector2(const Vector2& v);

	/** @return a copy of this vector */
	Vector2 cpy();

	/** @return The euclidian length */
	float len();

	/** @return The squared euclidian length */
	float len2();

	/** Sets this vector from the given vector
	 * @param v The vector
	 * @return This vector for chaining */
	Vector2& set(const Vector2& v);

	/** Sets the components of this vector
	 * @param x The x-component
	 * @param y The y-component
	 * @return This vector for chaining */
	Vector2& set(float x, float y);

	/** Substracts the given vector from this vector.
	 * @param v The vector
	 * @return This vector for chaining */
	Vector2& sub(const Vector2& v);

	/** Normalizes this vector
	 * @return This vector for chaining */
	Vector2& nor();

	/** Adds the given vector to this vector
	 * @param v The vector
	 * @return This vector for chaining */
	Vector2& add(const Vector2& v);

	/** Adds the given components to this vector
	 * @param x The x-component
	 * @param y The y-component
	 * @return This vector for chaining */
	Vector2& add(float x, float y);

	/** @param v The other vector
	 * @return The dot product between this and the other vector */
	float dot(const Vector2& v);

	/** Multiplies this vector by a scalar
	 * @param scalar The scalar
	 * @return This vector for chaining */
	Vector2& mul(float scalar);

	/** @param v The other vector
	 * @return the distance between this and the other vector */
	float dst(const Vector2& v);

	/** @param x The x-component of the other vector
	 * @param y The y-component of the other vector
	 * @return the distance between this and the other vector */
	float dst(float x, float y);

	/** @param v The other vector
	 * @return the squared distance between this and the other vector */
	float dst2(const Vector2& v);

	/** @param x The x-component of the other vector
	 * @param y The y-component of the other vector
	 * @return the squared distance between this and the other vector */
	float dst2(float x, float y);

	std::string toString();

	/** Substracts the other vector from this vector.
	 * @param x The x-component of the other vector
	 * @param y The y-component of the other vector
	 * @return This vector for chaining */
	Vector2& sub(float x, float y);

	/** NEVER EVER SAVE THIS REFERENCE! Do not use this unless you are aware of the side-effects, e.g. other methods might call this
	 * as well.
	 *
	 * @return a temporary copy of this vector. Use with care as this is backed by a single static Vector2 instance. v1.tmp().add(
	 *         v2.tmp() ) will not work! */
	Vector2& tmp();

	/** Multiplies this vector by the given matrix
	 * @param mat the matrix
	 * @return this vector */
	Vector2& mul(const class Matrix3& mat);

	/** Calculates the 2D cross product between this and the given vector.
	 * @param v the other vector
	 * @return the cross product */
	float crs(const Vector2& v);

	/** Calculates the 2D cross product between this and the given vector.
	 * @param x the x-coordinate of the other vector
	 * @param y the y-coordinate of the other vector
	 * @return the cross product */
	float crs(float x, float y);

	/** @return the angle in degrees of this vector (point) relative to the x-axis. Angles are counter-clockwise and between 0 and
	 *         360. */
	float angle();

	/** Rotates the Vector2 by the given angle, counter-clockwise.
	 * @param angle the angle in degrees
	 * @return the */
	Vector2& rotate(float angle);

	/** Linearly interpolates between this vector and the target vector by alpha which is in the range [0,1]. The result is stored
	 * in this vector.
	 *
	 * @param target The target vector
	 * @param alpha The interpolation coefficient
	 * @return This vector for chaining. */
	Vector2& lerp(const Vector2& target, float alpha);

	/**
	 * Compares this vector with the other vector, using the supplied
	 * epsilon for fuzzy equality testing.
	 * @param obj
	 * @param epsilon
	 * @return whether the vectors are the same.
	 */
	bool epsilonEquals(const Vector2& obj, float epsilon);
};
