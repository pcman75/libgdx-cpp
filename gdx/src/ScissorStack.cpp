#include "stdafx.h"
#include "ScissorStack.h"

std::vector<Rectang> ScissorStack::scissors;
Vector3 ScissorStack::tmp;
Rectang ScissorStack::viewport;

bool ScissorStack::pushScissors( Rectang scissor) 
{
	fix(scissor);

	if( scissors.size() == 0) 
    {
		if( scissor.width < 1 || scissor.height < 1) return false;
      glEnable(GL_SCISSOR_TEST);
	} 
    else 
    {
		// merge scissors
		Rectang parent = scissors[ scissors.size() - 1];
		float minX = parent.x > scissor.x ? parent.x : scissor.x;
		float maxX = parent.x + parent.width <  scissor.x + scissor.width ? parent.x + parent.width : scissor.x + scissor.width;
		if (maxX - minX < 1) return false;

		float minY = parent.y > scissor.y ? parent.y : scissor.y;
		float maxY = parent.y + parent.height < scissor.y + scissor.height ? parent.y + parent.height : scissor.y + scissor.height;
		if (maxY - minY < 1) return false;

		scissor.x = minX;
		scissor.y = minY;
		scissor.width = maxX - minX;
		scissor.height = 1 > maxY - minY ? 1 : maxY - minY;
	}
	scissors.push_back( scissor);
	glScissor((GLint)scissor.x, (GLint)scissor.y, (GLint)scissor.width, (GLint)scissor.height);
	return true;
}

/** Pops the current scissor Rectang from the stack and sets the new scissor area to the new TOS Rectang. In case no more
	* Rectangs are on the stack, {@link GL10#GL_SCISSOR_TEST} is disabled. */
void ScissorStack::popScissors () 
{
	scissors.pop_back();
	if( scissors.size() == 0)
		glDisable(GL_SCISSOR_TEST);
	else 
  {
		Rectang scissor = scissors[ scissors.size() - 1];
		glScissor((GLint)scissor.x, (GLint)scissor.y, (GLint)scissor.width, (GLint)scissor.height);
	}
}

void ScissorStack::fix (Rectang rect) 
{
	if (rect.width < 0) 
  {
		rect.width = -rect.width;
		rect.x -= rect.width;
	}
	if (rect.height < 0) 
  {
		rect.height = -rect.height;
		rect.y -= rect.height;
	}
}

	

/** Calculates a scissor Rectang in OpenGL ES window coordinates from a {@link Camera}, a transformation {@link Matrix4} and
	* an axis aligned {@link Rectang}. The Rectang will get transformed by the camera and transform matrices and is then
	* projected to screen coordinates. Note that only axis aligned Rectangs will work with this method. If either the Camera or
	* the Matrix4 have rotational components, the output of this method will not be suitable for
	* {@link GLCommon#glScissor(int, int, int, int)}.
	* @param camera the {@link Camera}
	* @param batchTransform the transformation {@link Matrix4}
	* @param area the {@link Rectang} to transform to window coordinates
	* @param scissor the Rectang to store the result in */
void ScissorStack::calculateScissors ( Camera* camera, Matrix4 batchTransform, Rectang area, Rectang scissor) 
{
	tmp.set(area.x, area.y, 0);
	tmp.mul(batchTransform);
	camera->project(tmp);
	scissor.x = tmp.x;
	scissor.y = tmp.y;

	tmp.set(area.x + area.width, area.y + area.height, 0);
	tmp.mul(batchTransform);
	camera->project(tmp);
	scissor.width = tmp.x - scissor.x;
	scissor.height = tmp.y - scissor.y;
}

/** @return the current viewport in OpenGL ES window coordinates based on the currently applied scissor */
Rectang ScissorStack::getViewport () 
{
	if (scissors.size() == 0) 
  {
		viewport.set(0, 0, Gdx.graphics->getWidth(), Gdx.graphics->getHeight());
		return viewport;
	} 
  else 
  {
		Rectang scissor = scissors[ scissors.size() - 1];
		viewport.set(scissor);
		return viewport;
	}
}

/** Transforms a point to real window coordinates (as oposed to OpenGL ES window coordinates), where the origin is in the top
	* left and the the y-axis is pointing downwards
	* @param camera the {@link Camera}
	* @param transformMatrix the transformation {@link Matrix4}
	* @param point the point to be transformed. */
void ScissorStack::toWindowCoordinates( Camera* camera, Matrix4 transformMatrix, Vector2 point) 
{
	tmp.set(point.x, point.y, 0);
	tmp.mul(transformMatrix);
	camera->project(tmp);
	tmp.y = Gdx.graphics->getHeight() - tmp.y;
	point.x = tmp.x;
	point.y = tmp.y;
}
