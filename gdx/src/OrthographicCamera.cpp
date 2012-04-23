#include "stdafx.h"
#include "OrthographicCamera.h"

OrthographicCamera::OrthographicCamera()
{
	this->zoom = 1;
	this->nearPlane = 0;
}

/** Constructs a new OrthographicCamera, using the given viewport width and height. For pixel perfect 2D rendering just supply
* the screen size, for other unit scales (e.g. meters for box2d) proceed accordingly.
*
* @param viewportWidth the viewport width
* @param viewportHeight the viewport height */
OrthographicCamera::OrthographicCamera(float viewportWidth, float viewportHeight)
{
	this->zoom = 1;
	this->viewportWidth = viewportWidth;
	this->viewportHeight = viewportHeight;
	this->nearPlane = 0;
	update();
}

/** Constructs a new OrthographicCamera, using the given viewport width and height. This will create a camera useable for
* iso-metric views. The diamond angle is specifies the angle of a tile viewed isometrically.
*
* @param viewportWidth the viewport width
* @param viewportHeight the viewport height
* @param diamondAngle the angle in degrees */
OrthographicCamera::OrthographicCamera(float viewportWidth, float viewportHeight, float diamondAngle)
{
	this->zoom = 1;
	this->viewportWidth = viewportWidth;
	this->viewportHeight = viewportHeight;
	this->nearPlane = 0;
	findDirectionForIsoView(diamondAngle, 0.00000001f, 20);
	update();
}

void OrthographicCamera::findDirectionForIsoView(float targetAngle, float epsilon, int maxIterations)
{
	float start = targetAngle - 5;
	float end = targetAngle + 5;
	float mid = targetAngle;

	int iterations = 0;
	float aMid = 0;
	while(fabs(targetAngle - aMid) > epsilon && iterations++ < maxIterations)
	{
		aMid = calculateAngle(mid);

		if(targetAngle < aMid)
		{
			end = mid;
		}
		else
		{
			start = mid;
		}
		mid = start + (end - start) / 2;
	}
	calculateDirection(mid, position);
	position.y = -position.y;
	lookAt(0, 0, 0);
	normalizeUp();
}

float OrthographicCamera::calculateAngle(float a)
{
	Vector3 camPos;
	calculateDirection(a, camPos);
	position.set(camPos.mul(30));
	lookAt(0, 0, 0);
	normalizeUp();
	update();

	Vector3 orig(0, 0, 0);
	Vector3 vec(1, 0, 0);
	project(orig);
	project(vec);
	Vector2 d(vec.x - orig.x, -(vec.y - orig.y));
	return d.angle();
}

void OrthographicCamera::calculateDirection(float angle, Vector3& dir)
{
	Matrix4 transform;
	dir = Vector3(-1, 0, 1).nor();
	transform.setToRotation(Vector3(1, 0, 1).nor(), angle);
	dir.mul(transform).nor();
}


void OrthographicCamera::update()
{
	projection.setToOrtho(zoom * -viewportWidth / 2, zoom * viewportWidth / 2, zoom * -viewportHeight / 2, zoom
		* viewportHeight / 2, fabs(nearPlane), fabs(farPlane));
	view.setToLookAt(position, m_tmp.set(position).add(direction), up);
	combined.set(projection);
	Matrix4::mul(combined.val, view.val);
	invProjectionView.set(combined);
	Matrix4::inv(invProjectionView.val);
	frustum.update(invProjectionView);
}


void OrthographicCamera::update(bool updateFrustum)
{
	projection.setToOrtho(zoom * -viewportWidth / 2, zoom * viewportWidth / 2, zoom * -viewportHeight / 2, zoom
		* viewportHeight / 2, fabs(nearPlane), fabs(farPlane));
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

/** Sets this camera to an orthographic projection using a viewport fitting the screen resolution, centered at
* (Gdx.graphics.getWidth()/2, Gdx.graphics.getHeight()/2), with the y-axis pointing up or down.
* @param yDown whether y should be pointing down */
void OrthographicCamera::setToOrtho(bool yDown)
{
	setToOrtho(yDown, ( float) Gdx.graphics->getWidth(), ( float) Gdx.graphics->getHeight());
}

/** Sets this camera to an orthographic projection, centered at (viewportWidth/2, viewportHeight/2), with the y-axis pointing up
* or down.
* @param yDown whether y should be pointing down.
* @param viewportWidth
* @param viewportHeight */
void OrthographicCamera::setToOrtho(bool yDown, float viewportWidth, float viewportHeight)
{
	if(yDown)
	{
		up.set(0, -1, 0);
		direction.set(0, 0, 1);
	}
	position.set(viewportWidth / 2.0f, viewportHeight / 2.0f, 0);
	this->viewportWidth = viewportWidth;
	this->viewportHeight = viewportHeight;
	update();
}

