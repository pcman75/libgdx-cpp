#include "stdafx.h"
#include "LinearInterpolator.h"


LinearInterpolator::LinearInterpolator() 
{
}
LinearInterpolator::~LinearInterpolator () 
{
}

void LinearInterpolator::finished () 
{
	delete this;
}

float LinearInterpolator::getInterpolation (float input) 
{
	return input;
}

Interpolator* LinearInterpolator::copy () 
{
	return new LinearInterpolator();
}