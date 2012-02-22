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

/** Encapsulates a ray having a starting position and a unit length direction.*/

class Ray
{
private:
	static Vector3 m_tmp;

public:
	Vector3 origin;
	Vector3 direction;

	/** Constructor, sets the starting position of the ray and the direction.
	 *
	 * @param origin The starting position
	 * @param direction The direction */
	Ray(const Vector3& origin, const Vector3& direction);

	/** @return a copy of this ray. */
	Ray cpy();

	/** Returns and endpoint given the distance. This is calculated as startpoint + distance * direction.
	 *
	 * @param distance The distance from the end point to the start point.
	 * @return The end point */
	Vector3 getEndPoint(float distance);

	/** Multiplies the ray by the given matrix. Use this to transform a ray into another coordinate system.
	 *
	 * @param matrix The matrix
	 * @return This ray for chaining. */
	Ray& mul(const Matrix4& matrix);

	/** {@inheritDoc} */
	std::string toString ();

	/** Sets the starting position and the direction of this ray.
	 *
	 * @param origin The starting position
	 * @param direction The direction
	 * @return this ray for chaining */
	Ray& set(const Vector3& origin, const Vector3& direction);

	/** Sets this ray from the given starting position and direction.
	 *
	 * @param x The x-component of the starting position
	 * @param y The y-component of the starting position
	 * @param z The z-component of the starting position
	 * @param dx The x-component of the direction
	 * @param dy The y-component of the direction
	 * @param dz The z-component of the direction
	 * @return this ray for chaining */
	Ray& set(float x, float y, float z, float dx, float dy, float dz);

	/** Sets the starting position and direction from the given ray
	 *
	 * @param ray The ray
	 * @return This ray for chaining */
	Ray& set(const Ray& ray);
};
