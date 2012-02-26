#include "stdafx.h"
#include "InputAdapter.h"

bool InputAdapter::keyDown(int keycode)
{
	return false;
}

bool InputAdapter::keyUp(int keycode)
{
	return false;
}

bool InputAdapter::keyTyped(char character)
{
	return false;
}

bool InputAdapter::touchDown(int x, int y, int pointer, int button)
{
	return false;
}

bool InputAdapter::touchUp(int x, int y, int pointer, int button)
{
	return false;
}

bool InputAdapter::touchDragged(int x, int y, int pointer)
{
	return false;
}

bool InputAdapter::touchMoved(int x, int y)
{
	return false;
}

bool InputAdapter::scrolled(int amount)
{
	return false;
}
