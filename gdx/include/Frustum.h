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
#include "Plane.h"
#include "Matrix4.h"
#include "BoundingBox.h"

class Frustum
{
protected:
	static Vector3 m_clipSpacePlanePoints[];
	static float m_clipSpacePlanePointsArray[8 * 3];

public:
	
	/** the six clipping planes, near, far, left, right, top, bottm **/
	Plane planes[6];

	/** eight points making up the near and far clipping "rectangles". order is counter clockwise, starting at bottom left **/
	Vector3 planePoints[8];

protected:
	float planePointsArray[8 * 3];

public:
	Frustum();

	/** Updates the clipping plane's based on the given inverse combined projection and view matrix, e.g. from an
	 * {@link OrthographicCamera} or {@link PerspectiveCamera}.
	 * @param inverseProjectionView the combined projection and view matrices. */
	void update(const Matrix4& inverseProjectionView);

	/** Returns wheter the point is in the frustum.
	 *
	 * @param point The point
	 * @return Wheter the point is in the frustum. */
	bool pointInFrustum(const Vector3& point);

	/** Returns wheter the given sphere is in the frustum.
	 *
	 * @param center The center of the sphere
	 * @param radius The radius of the sphere
	 * @return Wheter the sphere is in the frustum */
	bool sphereInFrustum(const Vector3& center, float radius);

	/** Returns wheter the given sphere is in the frustum not checking wheter it is behind the near and far clipping plane.
	 *
	 * @param center The center of the sphere
	 * @param radius The radius of the sphere
	 * @return Wheter the sphere is in the frustum */
	bool sphereInFrustumWithoutNearFar(const Vector3& center, float radius);

	/** Returns wheter the given {@link BoundingBox} is in the frustum.
	 *
	 * @param bounds The bounding box
	 * @return Wheter the bounding box is in the frustum */
	bool boundsInFrustum(BoundingBox& bounds);
};
