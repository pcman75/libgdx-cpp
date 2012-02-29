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

#include "Camera.h"
#include "Vector3.h"
#include "Vector2.h"
#include "MathUtils.h"

/** A camera with orthographic projection.*/
class GdxDllImportExport OrthographicCamera : public Camera
{
public:
	/** the zoom of the camera **/
	float zoom;
private:
	Vector3 m_tmp;

public:
	OrthographicCamera();

	/** Constructs a new OrthographicCamera, using the given viewport width and height. For pixel perfect 2D rendering just supply
	 * the screen size, for other unit scales (e.g. meters for box2d) proceed accordingly.
	 *
	 * @param viewportWidth the viewport width
	 * @param viewportHeight the viewport height */
	OrthographicCamera(float viewportWidth, float viewportHeight);

	/** Constructs a new OrthographicCamera, using the given viewport width and height. This will create a camera useable for
	 * iso-metric views. The diamond angle is specifies the angle of a tile viewed isometrically.
	 *
	 * @param viewportWidth the viewport width
	 * @param viewportHeight the viewport height
	 * @param diamondAngle the angle in degrees */
	OrthographicCamera(float viewportWidth, float viewportHeight, float diamondAngle);

	void findDirectionForIsoView(float targetAngle, float epsilon, int maxIterations);

private:
	float calculateAngle(float a);

	void calculateDirection(float angle, Vector3& dir);

public:
	virtual void update();

	
	virtual void update(bool updateFrustum);

	/** Sets this camera to an orthographic projection using a viewport fitting the screen resolution, centered at
	 * (Gdx.graphics.getWidth()/2, Gdx.graphics.getHeight()/2), with the y-axis pointing up or down.
	 * @param yDown whether y should be pointing down */
	void setToOrtho(bool yDown);

	/** Sets this camera to an orthographic projection, centered at (viewportWidth/2, viewportHeight/2), with the y-axis pointing up
	 * or down.
	 * @param yDown whether y should be pointing down.
	 * @param viewportWidth
	 * @param viewportHeight */
	void setToOrtho(bool yDown, float viewportWidth, float viewportHeight);
};
