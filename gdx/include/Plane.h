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
#include "Vector3.h"


/** A plane defined via a unit length normal and the distance from the origin, as you learned in your math class.
*/
class GdxDllImportExport Plane
{
public:
	/** Enum specifying on which side a point lies respective to the plane and it's normal. {@link PlaneSide#Front} is the side to
	* which the normal points.
	*/
	enum PlaneSide 
	{
		OnPlane, 
		Back, 
		Front
	};

	Vector3 normal;
	float d;

	/*construct a plane with normal and distance 0*/
	Plane();

	/** Constructs a new plane based on the normal and distance to the origin.
	* 
	* @param normal The plane normal
	* @param d The distance to the origin */
	Plane(const Vector3& normal, float d);

	/** Constructs a new plane based on the normal and a point on the plane.
	* 
	* @param normal The normal
	* @param point The point on the plane */
	Plane(const Vector3& normal, const Vector3& point);

	/** Constructs a new plane out of the three given points that are considered to be on the plane. The normal is calculated via a
	* cross product between (point1-point2)x(point2-point3)
	* 
	* @param point1 The first point
	* @param point2 The second point
	* @param point3 The third point */
	Plane(const Vector3& point1, const Vector3& point2, const Vector3& point3);

	/** Sets the plane normal and distance to the origin based on the three given points which are considered to be on the plane.
	* The normal is calculated via a cross product between (point1-point2)x(point2-point3)
	* 
	* @param point1
	* @param point2
	* @param point3 */
	void set(const Vector3& point1, const Vector3& point2, const Vector3& point3);

	/** Sets the plane normal and distance
	* 
	* @param nx normal x-component
	* @param ny normal y-component
	* @param nz normal z-component
	* @param d distance to origin */
	void set(float nx, float ny, float nz, float d);

	/** Calculates the shortest signed distance between the plane and the given point.
	* 
	* @param point The point
	* @return the shortest signed distance between the plane and the point */
	float distance(const Vector3& point);

	/** Returns on which side the given point lies relative to the plane and its normal. PlaneSide.Front refers to the side the
	* plane normal points to.
	* 
	* @param point The point
	* @return The side the point lies relative to the plane */
	PlaneSide testPoint(const Vector3& point);

	/** Returns whether the plane is facing the direction vector. Think of the direction vector as the direction a camera looks in.
	* This method will return true if the front side of the plane determined by its normal faces the camera.
	* 
	* @param direction the direction
	* @return whether the plane is front facing */
	bool isFrontFacing(const Vector3& direction);

	/** @return The normal */
	Vector3& getNormal();

	/** @return The distance to the origin */
	float getD();

	/** Sets the plane to the given point and normal.
	* 
	* @param point the point on the plane
	* @param normal the normal of the plane */
	void set(const Vector3& point, const Vector3& normal);

	/** Sets this plane from the given plane
	* 
	* @param plane the plane */
	void set( const Plane& plane);

	std::string toString();

};
