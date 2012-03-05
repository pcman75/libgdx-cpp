#include "stdafx.h"
#include "PerspectiveCamController.h"
#include "PerspectiveCamera.h"

PerspectiveCamController::PerspectiveCamController( const PerspectiveCamera& cam)
{
//    mode = TransformMode::Translate;
    mode = Translate;
    translated = false;

  lookAtPlane = Plane( Vector3(0, 1, 0), 0);
	xAxis = Vector3(1, 0, 0);
	yAxis = Vector3(0, 1, 0);

	this->cam = cam;
}

bool PerspectiveCamController::touchDown (int x, int y, int pointer, int button) 
{
	mode = Rotate;
	last.set(x, y);
	tCurr.set(x, y);
	return true;
}

bool PerspectiveCamController::touchUp (int x, int y, int pointer, int button) 
{
	mode = None;
	return true;
}

	
bool PerspectiveCamController::touchDragged (int x, int y, int pointer) 
{
	if (pointer != 0) return false;
	delta.set(x, y).sub(last);

	if (mode == Rotate) {
		point.set(cam.position).sub(lookAt);

		if (point.tmp().nor().dot(yAxis) < 0.9999f) {
			xAxis.set(cam.direction).crs(yAxis).nor();
			rotMatrix.setToRotation(xAxis, delta.y / 5);
			point.mul(rotMatrix);
		}

		rotMatrix.setToRotation(yAxis, -delta.x / 5);
		point.mul(rotMatrix);

		cam.position.set(point.add(lookAt));
		cam.lookAt(lookAt.x, lookAt.y, lookAt.z);
	}
	if (mode == Zoom) {
		cam.fieldOfView -= -delta.y / 10;
	}
	if (mode == Translate) {
		tCurr.set(x, y);
		translated = true;
	}

	cam.update();
	last.set(x, y);
	return true;
}

bool PerspectiveCamController::scrolled (int amount) 
{
  cam.fieldOfView -= -amount * Gdx.graphics->getDeltaTime() * 100;
	cam.update();
	return true;
}
