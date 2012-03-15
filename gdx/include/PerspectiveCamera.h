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
#include "Matrix4.h"
#include "Vector3.h"
#include "Camera.h"

/** A Camera with perspective projection.*/

class GdxDllImportExport PerspectiveCamera :
	public Camera
{
public:
	/** the field of view in degrees **/
	float fieldOfView;

private:
	Vector3 m_tmp;

public:
	PerspectiveCamera();

	/** Constructs a new {@link PerspectiveCamera} with the given field of view and viewport size. The apsect ratio is derrived from
	 * the viewport size.
	 *
	 * @param fieldOfView the field of view in degrees
	 * @param viewportWidth the viewport width
	 * @param viewportHeight the viewport height */
	PerspectiveCamera(float fieldOfView, float viewportWidth, float viewportHeight);

	virtual void update();
	virtual void update(bool updateFrustum);
};
