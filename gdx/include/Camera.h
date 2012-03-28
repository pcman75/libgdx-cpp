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
#include "Matrix4.h"
#include "Frustum.h"
#include "Ray.h"
#include "Gdx.h"



/** Base class for {@link OrthographicCamera} and {@link PerspectiveCamera}.*/

class Camera
{
public:

	/** the position of the camera **/
	Vector3 position;

	 /** the unit length direction vector of the camera **/
	Vector3 direction;
	/** the unit length up vector of the camera **/
	Vector3 up;

	/** the projection matrix **/
	Matrix4 projection;
	/** the view matrix **/
	Matrix4 view;
	/** the combined projection and view matrix **/
	Matrix4 combined;
	/** the inverse combined projection and view matrix **/
	Matrix4 invProjectionView;

	/** the near clipping plane distance, has to be positive **/
	float nearPlane;
	/** the far clipping plane distance, has to be positive **/
	float farPlane;

	/** the viewport width **/
	float viewportWidth;
	/** the viewport height **/
	float viewportHeight;

	/** the frustum **/
	Frustum frustum;
	

private:
	Matrix4 m_tmpMat;
	Vector3 m_tmpVec;
	Vector3 m_right;
	Ray m_ray;

public:
	Camera();

	/** Recalculates the projection and view matrix of this camera and the {@link Frustum} planes. Use this after you've manipulated
	 * any of the attributes of the camera. */
	virtual void update() = 0;

	/** Recalculates the projection and view matrix of this camera and the {@link Frustum} planes if <code>updateFrustum</code> is
	 * true. Use this after you've manipulated any of the attributes of the camera. */
	virtual void update(bool updateFrustum) = 0;

	/** Sets the current projection and model-view matrix of this camera. Only works with {@link GL10} and {@link GL11} of course.
	 * The parameter is there to remind you that it does not work with GL20. Make sure to call {@link #update()} before calling
	 * this method so all matrices are up to date.
	 *
	 * @param gl the GL10 or GL11 instance. */
	void apply();

	/** Recalculates the direction of the camera to look at the point (x, y, z).
	 * @param x the x-coordinate of the point to look at
	 * @param y the x-coordinate of the point to look at
	 * @param z the x-coordinate of the point to look at */
	void lookAt (float x, float y, float z);

	/** Normalizes the up vector by first calculating the right vector via a cross product between direction and up, and then
	 * recalculating the up vector via a cross product between right and direction. */
	void normalizeUp ();

	/** Rotates the direction and up vector of this camera by the given angle around the given axis. The direction and up vector
	 * will not be orthogonalized.
	 *
	 * @param angle the angle
	 * @param axisX the x-component of the axis
	 * @param axisY the y-component of the axis
	 * @param axisZ the z-component of the axis */
	void rotate (float angle, float axisX, float axisY, float axisZ);

	/** Moves the camera by the given amount on each axis.
	 * @param x the displacement on the x-axis
	 * @param y the displacement on the y-axis
	 * @param z the displacement on the z-axis */
	void translate (float x, float y, float z);

	/** Function to translate a point given in window (or window) coordinates to world space. It's the same as
	 * {@link GLU#gluUnProject(float, float, float, float[], int, float[], int, int[], int, float[], int)} but does not rely on
	 * OpenGL. The x- and y-coordinate of vec are assumed to be in window coordinates (origin is the top left corner, y pointing
	 * down, x pointing to the right) as reported by the touch methods in {@link Input}. A z-coordinate of 0 will return a point on
	 * the near plane, a z-coordinate of 1 will return a point on the far plane. This method allows you to specify the viewport
	 * position and dimensions in the coordinate system expected by {@link GLCommon#glViewport(int, int, int, int)}, with the
	 * origin in the bottom left corner of the screen.
	 *
	 * @param vec the point in window coordinates (origin top left)
	 * @param viewportX the coordinate of the top left corner of the viewport in glViewport coordinates (origin bottom left)
	 * @param viewportY the coordinate of the top left corner of the viewport in glViewport coordinates (origin bottom left)
	 * @param viewportWidth the width of the viewport in pixels
	 * @param viewportHeight the height of the viewport in pixels */
	void unproject(Vector3& vec, float viewportX, float viewportY, float viewportWidth, float viewportHeight);

	/** Function to translate a point given in window (or window) coordinates to world space. It's the same as
	 * {@link GLU#gluUnProject(float, float, float, float[], int, float[], int, int[], int, float[], int)} but does not rely on
	 * OpenGL. The viewport is assuemd to span the whole screen and is fetched from {@link Graphics#getWidth()} and
	 * {@link Graphics#getHeight()}. The x- and y-coordinate of vec are assumed to be in window coordinates (origin is the top left
	 * corner, y pointing down, x pointing to the right) as reported by the touch methods in {@link Input}. A z-coordinate of 0
	 * will return a point on the near plane, a z-coordinate of 1 will return a point on the far plane.
	 *
	 * @param vec the point in window coordinates */
	void unproject(Vector3& vec);

	/** Projects the {@link Vector3} given in object/world space to window coordinates. It's the same as
	 * {@link GLU#gluProject(float, float, float, float[], int, float[], int, int[], int, float[], int)} with one small deviation:
	 * The viewport is assumed to span the whole screen. The window coordinate system has its origin in the <b>bottom</b> left,
	 * with the y-axis pointing <b>upwards</b> and the x-axis pointing to the right. This makes it easily useable in conjunction
	 * with {@link SpriteBatch} and similar classes.
	 * @param vec the position in object/world space. */
	void project(Vector3& vec);

	/** Projects the {@link Vector3} given in object/world space to window coordinates. It's the same as
	 * {@link GLU#gluProject(float, float, float, float[], int, float[], int, int[], int, float[], int)} with one small deviation:
	 * The viewport is assumed to span the whole screen. The window coordinate system has its origin in the <b>bottom</b> left,
	 * with the y-axis pointing <b>upwards</b> and the x-axis pointing to the right. This makes it easily useable in conjunction
	 * with {@link SpriteBatch} and similar classes. This method allows you to specify the viewport position and dimensions in the
	 * coordinate system expected by {@link GLCommon#glViewport(int, int, int, int)}, with the origin in the bottom left corner of
	 * the screen.
	 *
	 * @param vec the point in object/world space
	 * @param viewportX the coordinate of the top left corner of the viewport in glViewport coordinates (origin bottom left)
	 * @param viewportY the coordinate of the top left corner of the viewport in glViewport coordinates (origin bottom left)
	 * @param viewportWidth the width of the viewport in pixels
	 * @param viewportHeight the height of the viewport in pixels */
	void project(Vector3& vec, float viewportX, float viewportY, float viewportWidth, float viewportHeight);

	

	/** Creates a picking {@link Ray} from the coordinates given in window coordinates. It is assumed that the viewport spans the
	 * whole screen. The window coordinates origin is assumed to be in the top left corner, its y-axis pointing down, the x-axis
	 * pointing to the right. The returned instance is not a new instance but an internal member only accessible via this function.
	 *
	 * @param x the x-coordinate in window coordinates.
	 * @param y the y-coordinate in window coordinates.
	 * @return the picking Ray. */
	Ray& getPickRay (float x, float y, float viewportX, float viewportY, float viewportWidth, float viewportHeight);

	/** Creates a picking {@link Ray} from the coordinates given in window coordinates. It is assumed that the viewport spans the
	 * whole screen. The window coordinates origin is assumed to be in the top left corner, its y-axis pointing down, the x-axis
	 * pointing to the right. The returned instance is not a new instance but an internal member only accessible via this function.
	 *
	 * @param x the x-coordinate in window coordinates.
	 * @param y the y-coordinate in window coordinates.
	 * @return the picking Ray. */
	Ray& getPickRay (float x, float y);
};
