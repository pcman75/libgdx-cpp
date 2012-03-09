#include "stdafx.h"
#include "GameObject.h"

GameObject::GameObject(float x, float y, float width, float height) 
	:position(x, y), bounds(x - width / 2, y - height / 2, width, height)
{
}

