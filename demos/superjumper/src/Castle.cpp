#include "stdafx.h"
#include "Castle.h"

const float Castle::CASTLE_WIDTH = 1.7f;
const float Castle::CASTLE_HEIGHT = 1.7f;


Castle::Castle(float x, float y) 
	: GameObject(x, y, CASTLE_WIDTH, CASTLE_HEIGHT)
{	
}

