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

#include "Vector3.h"

/** Encapsulates an axis aligned bounding box represented by a minimum and a maximum Vector. Additionally you can query for the
 * bounding box's center, dimensions and corner points.
 */
class BoundingBox
{
private:
	Vector3 m_crn[8];
	Vector3 m_min;
	Vector3 m_max;
	Vector3 m_cnt;
	Vector3 m_dim;
	bool m_crn_dirty;

	~BoundingBox();

	/** @return the center of the bounding box */
	Vector3 getCenter();

protected:
	void updateCorners();

public:
	/** @return the corners of this bounding box */
	const Vector3* const getCorners();

	/** @return The dimensions of this bounding box on all three axis */
	const Vector3& getDimensions();

	/** @return The minimum vector */
	const Vector3& getMin();

	/** @return The maximum vector */
	const Vector3& getMax();

	/** Constructs a new bounding box with the minimum and maximum vector set to zeros. */
	BoundingBox();

	/** Constructs a new bounding box from the given bounding box.
	 *
	 * @param bounds The bounding box to copy */
	BoundingBox(const BoundingBox& bounds);

	/** Constructs the new bounding box using the given minimum and maximum vector.
	 *
	 * @param minimum The minimum vector
	 * @param maximum The maximum vector */
	BoundingBox(const Vector3& minimum, const Vector3& maximum);

	/** Sets the given bounding box.
	 *
	 * @param bounds The bounds.
	 * @return This bounding box for chaining. */
	BoundingBox& set(const BoundingBox& bounds);

	/** Sets the given minimum and maximum vector.
	 *
	 * @param minimum The minimum vector
	 * @param maximum The maximum vector
	 * @return This bounding box for chaining. */
	BoundingBox& set(const Vector3& minimum, const Vector3& maximum);

	/** Sets the bounding box minimum and maximum vector from the given points.
	 *
	 * @param points The points.
	 * @return This bounding box for chaining. */
	BoundingBox& set(const Vector3* points, int numPoints);

	/** Sets the bounding box minimum and maximum vector from the given points.
	 *
	 * @param points The points.
	 * @return This bounding box for chaining. */
	BoundingBox& set(std::list<Vector3> points);

	/** Sets the minimum and maximum vector to positive and negative infinity.
	 *
	 * @return This bounding box for chaining. */
	BoundingBox& inf();

	/** Extends the bounding box to incorporate the given {@link Vector3}.
	 *
	 * @param point The vector
	 * @return This bounding box for chaining. */
	BoundingBox& ext(const Vector3& point);

	/** Sets the minimum and maximum vector to zeros
	 *
	 * @return This bounding box for chaining. */
	BoundingBox& clr();

	/** Returns wheter this bounding box is valid. This means that m_min != m_max and m_min < m_max.
	 *
	 * @return True in case the bounding box is valid, false otherwise */
	bool isValid();

	/** Extends this bounding box by the given bounding box.
	 *
	 * @param a_bounds The bounding box
	 * @return This bounding box for chaining. */
	BoundingBox& ext(BoundingBox& a_bounds);

	/** Multiplies the bounding box by the given matrix. This is achieved by multiplying the 8 corner points and then calculating
	 * the minimum and maximum vectors from the transformed points.
	 *
	 * @param matrix The matrix
	 * @return This bounding box for chaining. */
	BoundingBox& mul(const class Matrix4& matrix);

	/** Returns wheter the given bounding box is contained in this bounding box.
	 * @param bounds The bounding box
	 * @return Wheter the given bounding box is contained */
	bool contains(BoundingBox& bounds);

	/** Returns wheter the given vector is contained in this bounding box.
	 * @param v The vector
	 * @return Wheter the vector is contained or not. */
	bool contains(const Vector3& v);

	std::string toString();

	/** Extends the bounding box by the given vector.
	 *
	 * @param x The x-coordinate
	 * @param y The y-coordinate
	 * @param z The z-coordinate
	 * @return This bounding box for chaining. */
	BoundingBox& ext(float x, float y, float z);
};
