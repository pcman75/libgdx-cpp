#include "stdafx.h"
#include "Spring.h"


const float Spring::SPRING_WIDTH = 0.3f;
const float Spring::SPRING_HEIGHT = 0.3f;


Spring::Spring(float x, float y) 
	: GameObject(x, y, SPRING_WIDTH, SPRING_HEIGHT)
{
}

