#include "stdafx.h"
#include "PerspectiveCamera.h"

PerspectiveCamera::PerspectiveCamera()
{
	fieldOfView = 67;
}

/** Constructs a new {@link PerspectiveCamera} with the given field of view and viewport size. The apsect ratio is derrived from
* the viewport size.
*
* @param fieldOfView the field of view in degrees
* @param viewportWidth the viewport width
* @param viewportHeight the viewport height */
PerspectiveCamera::PerspectiveCamera(float fieldOfView, float viewportWidth, float viewportHeight)
{
	fieldOfView = 67;
	this->fieldOfView = fieldOfView;
	this->viewportWidth = viewportWidth;
	this->viewportHeight = viewportHeight;
	update();
}

void PerspectiveCamera::update()
{
	float aspect = viewportWidth / viewportHeight;
	projection.setToProjection(fabs(nearPlane), fabs(farPlane), fieldOfView, aspect);
	view.setToLookAt(position, m_tmp.set(position).add(direction), up);
	combined.set(projection);
	Matrix4::mul(combined.val, view.val);
	invProjectionView.set(combined);
	Matrix4::inv(invProjectionView.val);
	frustum.update(invProjectionView);
}

void PerspectiveCamera::update(bool updateFrustum)
{
	float aspect = viewportWidth / viewportHeight;
	projection.setToProjection(fabs(nearPlane), fabs(farPlane), fieldOfView, aspect);
	view.setToLookAt(position, m_tmp.set(position).add(direction), up);
	combined.set(projection);
	Matrix4::mul(combined.val, view.val);

	if(updateFrustum)
	{
		invProjectionView.set(combined);
		Matrix4::inv(invProjectionView.val);
		frustum.update(invProjectionView);
	}
}

